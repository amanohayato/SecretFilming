#include "PauseMunu.h"
#include"../../../../Define.h"
#include"../../../../Input/InputChecker.h"
#include"../../../../Graphic/Sprite.h"
#include"../../../../Math/MathHelper.h"
#include"../../../../Sound/Sound.h"

PauseMunu::PauseMunu()
{
}

void PauseMunu::start()
{
	baseInit();

	menuSize_ = 3;
}

void PauseMunu::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 10) % 360;

	// スティックを上に傾けたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_UP)) moveCursor(-1);
	// スティックを下に傾けたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_DOWN)) moveCursor(1);
	// 決定ボタンを押したら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();
}

void PauseMunu::draw() const
{
	// 背景を暗くする画像を描画
	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

	// “ポーズ”書かれた画像を描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PAUSE_BG, Vector2::Zero);

	// “ゲームに戻る”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RETURN_GAME, Vector2(650.0f, 270.0f));

	// “オプション”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GO_TO_OPTION, Vector2(650.0f, 500.0f));

	// “タイトルに戻る”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RETURN_TITLE, Vector2(650.0f, 730.0f));

	// メニューカーソルの画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(500 + (MathHelper::Sin((float)sinCount_) * 30), 270.0f + (cursorPos_ * 230))); // , MathHelper::Abs(MathHelper::Sin((float)sinCount_))
}

void PauseMunu::end()
{
}

void PauseMunu::decisionCheck()
{
	// カーソルSEを再生
	Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

	switch (cursorPos_)
	{
	case 0:

		nextScene_ = SceneType::SCENE_GAMEPLAY;
		isChangeScene_ = true;
		break;

	case 1:

		nextSubScene_ = SubSceneType::OPTION;
		isChangeSubScene_ = true;
		break;

	case 2:

		nextSubScene_ = SubSceneType::DECISION_MENU;
		isChangeSubScene_ = true;
		break;

	default:
		break;
	}
}
