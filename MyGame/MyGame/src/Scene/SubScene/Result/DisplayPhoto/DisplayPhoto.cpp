#include "DisplayPhoto.h"
#include"../../../../Define.h"
#include"../../../../Camera/CaptureScreen.h"
#include"../../../../Sound/Sound.h"

DisplayPhoto::DisplayPhoto()
{
}

void DisplayPhoto::start()
{
	// 撮影した写真をスコア順にソートする
	CaptureScreen::getInstance().sortVectorToScore();

	// 表示する写真の枚数を最大値にする
	photoNumber_ = maxPhotoNumber_;

	// ゲーム中に取った写真枚数が maxPhotoNumber より少なかったら
	if (photoNumber_ > CaptureScreen::getInstance().getSize())
	{
		// 調整をする
		photoNumber_ = CaptureScreen::getInstance().getSize();
	}

	CaptureScreen::getInstance().setResultDrawGraphHandle(photoNumber_);
	

	// 写真をリストに入れる為のポインタ
	std::shared_ptr<ScalingSprite> photoImage;

	// 写真出現演出クラスを設定
	for (int i = (photoNumber_ - 1); i > -1; i--)
	{
		photoImage = std::make_shared<ScalingSprite>
			(
				Vector2(1, 1),
				Vector2(0.25f, 0.25f),
				0.5f);

		photoAnims_.push_back(photoImage);
	}

	// 現在の表示写真番号を０にする
	displayPhotoCount_ = 0;

	isStampStart_ = false;

	isAnimReturn_ = false;
}

void DisplayPhoto::update(float deltaTime)
{
	// 表示する写真がなければ処理を行わない
	if (photoNumber_ == 0) return;

	for (int i = 0; i <= displayPhotoCount_; i++)
	{
		photoAnims_[i]->update(deltaTime);
	}

	if (isStampStart_ && photoAnims_[displayPhotoCount_]->isAnimationEnd())
	{
		if (isAnimReturn_)
		{
			
		}
		else
		{
			isAnimReturn_ = true;

			Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

			for (int i = 0; i <= displayPhotoCount_; i++)
			{
				photoAnims_[i] = std::make_shared<ScalingSprite>
					(
						Vector2(0.20f, 0.20f),
						Vector2(0.21f, 0.21f),
						0.02f);
			}
		}
	}

	if (displayPhotoCount_ < (photoNumber_ - 1) && photoAnims_[displayPhotoCount_]->isAnimationEnd()) 
		displayPhotoCount_++;
}

void DisplayPhoto::draw() const
{
	// 表示する写真がなければ処理を行わない
	if (photoNumber_ == 0) return;

	// 写真の表示座標の配列
	Vector2 positions[] =
	{
		Vector2(680,  20),
		Vector2(820, 260),
		Vector2(680, 460),
		Vector2(1400, 400),
		Vector2(820, 710),
		Vector2(1250, 650)
	};

	for (int i = 0; i <= displayPhotoCount_; i++)
	{
		CaptureScreen::getInstance().drawResultPhoto
		(
			i,
			positions[i] + Vector2((float)WINDOW_WIDTH * 0.125f, (float)WINDOW_HEIGHT * 0.125f),
			(Vector2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT) / 2.f), 
			1.0f,
			photoAnims_[i]->getCurScale()
		);
	}
}

void DisplayPhoto::end()
{
	photoAnims_.clear();
}

void DisplayPhoto::stampStart()
{
	// 表示する写真がなければ処理を行わない
	if (photoNumber_ == 0) return;

	isStampStart_ = true;

	for (int i = 0; i <= displayPhotoCount_; i++)
	{
		photoAnims_[i] = std::make_shared<ScalingSprite>
			(
				Vector2(0.21f, 0.21f),
				Vector2(0.20f, 0.20f),
				0.02f);
	}
}

bool DisplayPhoto::isEndAnimation()
{
	// 表示する写真がなければアニメーションが終了していると返す
	if (photoNumber_ == 0) return true;

	return photoAnims_[(photoNumber_ - 1)]->isAnimationEnd();
}
