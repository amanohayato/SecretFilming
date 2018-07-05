#include "Option.h"
#include"../../../../Input/InputChecker.h"
#include"../../../../Graphic/Sprite.h"
#include"../../../../Sound/Sound.h"
#include"../../../Manager/GameDataManager.h"

Option::Option(SubSceneType nextSubScene)
{
	nextSubScene_ = nextSubScene;
}

void Option::start()
{
	baseInit();

	// 現在のカメラ感度を取得
	cameraSens_ = (int)(GameDataManager::getInstance().getCameraSens() * 10.f);

	// 現在のBGM音量を取得
	bgmVolume_ = (int)(Sound::GetInstance().IsAllBGMVolume() * 10.f);

	// 現在のSE音量を取得
	seVolume_ = (int)(Sound::GetInstance().IsAllSEVolume() * 10.f);

	menuSize_ = 4;
}

void Option::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 1) % 360;

	bool isLongPress = false;

	// スティックを上に傾け始めたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_UP)) moveCursor(-1);
	// スティックを下に傾け始めたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_DOWN)) moveCursor(1);

	// スティックを左に傾けたら
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::STICK_LEFT))
	{
		isLongPress = true;

		if (isHighSpeedMove_)
		{
			changeParameter(-1);
		}
		else if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_LEFT))
		{
			changeParameter(-1);
		}
	}
	// スティックを右に傾けたら
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::STICK_RIGHT))
	{
		isLongPress = true;

		if (isHighSpeedMove_)
		{
			changeParameter(1);
		}
		else if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_RIGHT))
		{
			changeParameter(1);
		}
	}
	
	// 決定ボタンを押したら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();

	if (isLongPress)
	{
		longPressTimer_ += deltaTime;

		if (longPressTimer_ > longPressTime_)
		{
			isHighSpeedMove_ = true;
		}
	}
	else
	{
		longPressTimer_ = 0.0f;
		isHighSpeedMove_ = false;
	}
}

void Option::draw() const
{
	// 背景を暗くする画像を描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

	// 背景画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GO_TO_OPTION, Vector2(560.f, 100.f));

	// メニュー項目“カメラ感度設定”の画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CAMERA_SENSITIVITY, Vector2(140.f, 400.f));

	// メニュー項目“BGM音量設定”の画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_BGM_VOLUME, Vector2(140.f, 570.f));

	// メニュー項目“SE音量設定”の画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_SE_VOLUME, Vector2(140.f, 740.f));

	// メニュー項目“メニューへ戻る”の画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_EXIT , Vector2(140.f, 910.f));

	for (int i = 0; i < 3; i++)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_FLAME, Vector2(740.f, 470.f + ((float)i * 170.f)));
	}
	
	for (int i = 0; i < cameraSens_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (0.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)cameraSens_ * 100.f), 400.f + (0.f * 170.f)));

	for (int i = 0; i < bgmVolume_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (1.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)bgmVolume_ * 100.f), 400.f + (1.f * 170.f)));

	for (int i = 0; i < seVolume_; i++)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_OPTION_BAR, Vector2(740.f + ((float)i * 100.f), 470.f + (2.f * 170.f)), i);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_OPTION_CURSOR, Vector2(640.f + ((float)seVolume_ * 100.f), 400.f + (2.f * 170.f)));

	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(40.f, 400.f + ((float)cursorPos_ * 170.f)));
}

void Option::end()
{
}

void Option::decisionCheck()
{
	if (cursorPos_ == 3)
	{
		// カーソルSEを再生
		Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

		isChangeSubScene_ = true;
	}
}

void Option::changeParameter(int value)
{
	// セレクトSEを再生
	Sound::GetInstance().PlaySE(SE_ID::CURSOR_MOVE_SE);

	// カーソル位置によって分岐
	switch (cursorPos_)
	{
		// カーソル位置が“カメラ感度設定”だったら
	case 0:

		// カメラ感度を低下
		cameraSens_ += value;
		if (cameraSens_ < 1) cameraSens_ = 1;
		if (cameraSens_ > 10) cameraSens_ = 10;

		// 実際にカメラ感度を変更
		GameDataManager::getInstance().setCameraSens((float)cameraSens_ / 10);

		break;

		// カーソル位置が“BGM音量設定”だったら
	case 1:

		// BGM音量を低下
		bgmVolume_ += value;
		if (bgmVolume_ < 1) bgmVolume_ = 1;
		if (bgmVolume_ > 10) bgmVolume_ = 10;

		// 実際にBGMの音量を変更
		Sound::GetInstance().SetAllBGMVolume((float)bgmVolume_ / 10);

		break;

		// カーソル位置が“SE音量設定”だったら
	case 2:

		// SE音量を低下
		seVolume_ += value;
		if (seVolume_ < 1) seVolume_ = 1;
		if (seVolume_ > 10) seVolume_ = 10;

		// 実際にSEの音量を変更
		Sound::GetInstance().SetAllSEVolume((float)seVolume_ / 10);

		break;

	default:
		break;
	}
}