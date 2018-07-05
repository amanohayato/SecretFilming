#include "MainMenu.h"
#include "../../../../Input/InputChecker.h"
#include "../../../../Graphic/Sprite.h"
#include "../../../../Sound/Sound.h"
#include "../../../../Math/MathHelper.h"

MainMenu::MainMenu()
{
}

void MainMenu::start()
{
	baseInit();

	menuSize_ = 3;
}

void MainMenu::update(float deltaTime)
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

void MainMenu::draw() const
{
	// タイトルロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_TITLELOGO, Vector2(220, 30));

	// “ゲームスタート”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GAME_START, Vector2(640.0f, 460.0f));

	// “オプション”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_GO_TO_OPTION, Vector2(640.0f, 600.0f));

	// “ゲーム終了”のメニュー項目の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_EXIT, Vector2(640.0f, 740.0f));

	// メニューカーソルの画像の描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MENU_CURSOR, Vector2(440.0f + (MathHelper::Sin((float)sinCount_) * 30), 460.0f + (cursorPos_ * 140)));
}

void MainMenu::end()
{
}

void MainMenu::decisionCheck()
{
	// カーソルSEを再生
	Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

	switch (cursorPos_)
	{
	case 0:

		nextScene_ = SceneType::SCENE_TUTORIAL;
		isChangeScene_ = true;
		break;

	case 1:

		nextSubScene_ = SubSceneType::OPTION;
		isChangeSubScene_ = true;
		break;

	case 2:

		isGameEnd_ = true;
		break;
	}
}
