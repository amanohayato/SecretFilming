#include "ResultScene.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Graphic/Sprite.h"
#include"../../Define.h"
#include"../../Input/InputChecker.h"
#include"../../Sound/Sound.h"
#include"../../Math/MathHelper.h"
#include"../Manager/GameDataManager.h"
#include"../../Camera/CaptureScreen.h"
#include"../../Graphic/DrawNumber.h"


ResultScene::ResultScene()
{
	displayPhoto_ = std::make_shared<DisplayPhoto>();
	scoreSheet_ = std::make_shared<ScoreSheet>();
	decisionMenu_ = std::make_shared<DecisionMenu>(SceneType::SCENE_GAMEPLAY, SubSceneType::NONE, SPRITE_ID::Game_over_retry_UI);
}

void ResultScene::start()
{
	// 基本の初期化関数を呼ぶ
	baseInit();

	// ゲームをクリアしたかの情報を取得する
	isClear_ = (GameDataManager::getInstance().getScore() >= 100);

	// メニュー表示フラグを切る
	displayMenu_ = false;

	isStamp_ = false;

	// 次のシーンを“エントランスシーン”にセットする
	next_ = SceneType::SCENE_ENTRANCE;

	// リザルトBGMを再生
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_RESULT, DX_PLAYTYPE_LOOP);

	displayPhoto_->start();
	scoreSheet_->start();
	decisionMenu_->start();
}

void ResultScene::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 10) % 360;

	displayPhoto_->update(deltaTime);
	scoreSheet_->update(deltaTime);

	if (displayMenu_)
	{
		decisionMenu_->update(deltaTime);

		if (decisionMenu_->isChangeScene())
		{
			next_ = decisionMenu_->nextScene();
			isEnd_ = true;
		}

		if (decisionMenu_->isChangeSubScene())
		{
			next_ = SceneType::SCENE_ENTRANCE;
			isEnd_ = true;
		}
	}

	if (isStamp_)
	{
		if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::ANY_BUTTON))
		{
			if (isClear_)
			{
				// 次のシーンを“エントランスシーン”にセットする
				next_ = SceneType::SCENE_ENTRANCE;
				isEnd_ = true;
			}
			else
			{
				displayMenu_ = true;
			}
		}
	}
	else
	{
		if (displayPhoto_->isEndAnimation())
		{
			displayPhoto_->stampStart();
			scoreSheet_->stampStart();

			isStamp_ = true;
		}
	}

	
}

void ResultScene::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RESULT_BG, Vector2::Zero);
	

	if (isClear_)
	{
		// ゲームクリアのロゴの描画
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAME_CLEAR_UI , Vector2(100.0f, 110.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::A_Lot_Of_Coin_ , Vector2(1280.0f, 70.0f));
	}
	else
	{
		// ゲームオーバーのロゴの描画
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAME_OVER_UI, Vector2(100.0f, 110.0f));
		Sprite::GetInstance().Draw(SPRITE_ID::Less_Coin_, Vector2(1380.0f, 20.0f));
	}
	displayPhoto_->draw();
	scoreSheet_->draw();

	if (displayMenu_)
	{
		// “PLESS_ANY_BUTTON”と書かれたロゴの描画
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PRESS_ANY_BUTTON_UI, Vector2(670.0f, 750.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));

		decisionMenu_->draw();
	}

	//// “リトライ”と書かれたロゴ + 背景を暗くする画像の描画
	//Sprite::GetInstance().Draw(SPRITE_ID::Game_over_retry_UI, Vector2::Zero);

	//// “はい”と書かれたロゴの描画
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_YES_UI, Vector2(450.0f, 640.0f));

	//// “いいえ”と書かれたロゴの描画
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_NO_UI, Vector2(1240.0f, 640.0f));

	//// メニューカーソルの描画
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(330.0f + (cursorPos_ * 790), 650.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void ResultScene::end()
{
	displayPhoto_->end();
	scoreSheet_->end();
	decisionMenu_->end();

	// メインメニューのBGMを停止する
	Sound::GetInstance().StopBGM();
}
