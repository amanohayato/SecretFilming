#include "DecisionMenu.h"
#include "../../../../Input/InputChecker.h"
#include "../../../../Graphic/Sprite.h"
#include "../../../../Sound/Sound.h"
#include "../../../../Math/MathHelper.h"


DecisionMenu::DecisionMenu(SceneType afterScene, SubSceneType beforeSubScene, SPRITE_ID mainLabel)
{
	afterScene_ = afterScene;
	beforeSubScene_ = beforeSubScene;
	mainLabelType_ = mainLabel;
}

void DecisionMenu::start()
{
	baseInit();

	menuSize_ = 2;
}

void DecisionMenu::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 10) % 360;

	// スティックを左に傾けたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_LEFT)) moveCursor(-1);
	// スティックを右に傾けたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::STICK_RIGHT)) moveCursor(1);
	// 決定ボタンを押したら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON)) decisionCheck();
}

void DecisionMenu::draw() const
{
	// クソ実装（後で補正）
	if (mainLabelType_ == SPRITE_ID::Game_over_retry_UI)
	{
		// 確認メニューの背景の表示
		Sprite::GetInstance().Draw(mainLabelType_, Vector2(0, 0));
	}
	else
	{
		// 背景を暗くする画像を描画
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);

		// 確認メニューの背景の表示
		Sprite::GetInstance().Draw(mainLabelType_, Vector2(560, 200));
	}

	// “はい”と書かれたロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_YES_UI, Vector2(450.0f, 640.0f));

	// “いいえ”と書かれたロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_NO_UI, Vector2(1240.0f, 640.0f));

	// メニューカーソルの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(330.0f + (cursorPos_ * 790), 650.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void DecisionMenu::end()
{
}

void DecisionMenu::decisionCheck()
{
	// カーソルSEを再生
	Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

	switch (cursorPos_)
	{
	case 0:
		nextScene_ = afterScene_;
		isChangeScene_ = true;
		break;

	case 1:

		nextSubScene_ = beforeSubScene_;
		isChangeSubScene_ = true;
		break;
	}
}
