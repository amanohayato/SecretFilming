#pragma once
#include "../../../Sound/Sound.h"
#include "../../../Graphic/TextBox.h"
#include "../../../Graphic/Sprite.h"
#include "../../../Input/InputChecker.h"

// チュートリアルでの指示一括りの処理
class TutorialCommand
{
public:
	virtual ~TutorialCommand() {}

	virtual void onStart() = 0;
	virtual void onUpdate(float deltaTime) = 0;
	virtual void onDraw()const = 0;
	virtual void onEnd() = 0;
	virtual void setText() = 0;

	void start();
	void update(float deltaTime);
	void draw()const;
	void end();

	bool isCommandEnd() { return isCommandEnd_; }

protected:

	// "A_Push"の画像を表示するフラグ
	bool displayA_Push_{ false };

	// "Y_Push"の画像を表示するフラグ
	bool displayY_Push_{ false };

	// "Y_Push"の画像を表示するフラグ
	bool displayLT_Push_{ false };

	// "Y_Push"の画像を表示するフラグ
	bool displayRT_Push_{ false };

	// 画像点滅用カウント
	int sinCount_{ 0 };

	// 指示が終了したフラグ
	bool isCommandEnd_{ false };

	// テキスト表示クラス
	TextBox textBox_{};

	// テキストボックスの表示位置
	Vector2 textBoxPos_{ 200.0f, 800.0f };

	// テキストボックスの大きさ
	Vector2 textBoxSize_{ 1200.0f, 150.0f };

	// "A_Push"の画像の表示位置
	Vector2 A_PushPos_{ 1250.0f, 800.0f };

	// "A_Push"の画像の表示位置
	Vector2 Push_Arrow_Pos_{ 1268.0f, 760.0f };
};