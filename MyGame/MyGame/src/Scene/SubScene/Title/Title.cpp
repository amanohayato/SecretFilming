#include "Title.h"
#include"../../../Input/InputChecker.h"
#include"../../../Graphic/Sprite.h"
#include"../../../Math/MathHelper.h"
#include"../../../Sound/Sound.h"

Title::Title()
{
}

void Title::start()
{
	baseInit();
}

void Title::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 10) % 360;

	// いずれかの入力があったら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::ANY_BUTTON)) {

		// セレクトSEを再生
		Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

		// メインメニューへ飛ぶ
		nextSubScene_ = SubSceneType::MAIN_MENU;
		isChangeSubScene_ = true;
	}
}

void Title::draw() const
{
	// タイトルロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_TITLELOGO, Vector2(220, 30));

	// タイトルロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_SOZAI_TEIKYOU_TEXT, Vector2(1600, 1000));

	// “PLESS_ANY_BUTTON”と書かれたロゴの描画
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PRESS_ANY_BUTTON_UI, Vector2(340.0f, 680.0f), MathHelper::Abs(MathHelper::Sin((float)sinCount_)));
}

void Title::end()
{
}
