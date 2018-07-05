#include "DemoMovieScene.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Input/InputChecker.h"

DemoMovieScene::DemoMovieScene()
{
}

void DemoMovieScene::start()
{
	// このシーンの終了フラグをOffにする
	isEnd_ = false;

	// 次のシーンを“エントランスシーン”にセットする
	next_ = SceneType::SCENE_ENTRANCE;

	// デモムービーの再生開始
	// デモムービーの再生履歴の情報をもっと上層のクラスで持つ必要あり

}

void DemoMovieScene::update(float deltaTime)
{
	// 点滅カウントの更新
	sinCount_ = (sinCount_ + 1) % 360;

	// Aボタンが押されたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON))
	{
		// このシーンの終了条件をOnにする
		isEnd_ = true;
	}

	// デモムービーの再生が終了したら
	if (false)
	{
		// このシーンの終了条件をOnにする
		isEnd_ = true;
	}
}

void DemoMovieScene::draw() const
{
	// デモムービーの描画


	//  "Ｏボタンでメインメニューへ" の描画
	//Sprite::GetInstance().Draw(SPRITE_ID:: , Vector2::Zero);

	// ここから下は仮の表示
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100, GetColor(255, 255, 255), "現在、デモシーンです");

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "デモムービーを再生中");

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, GetColor(255, 255, 255), "Ｏボタンでタイトルへ");
}

void DemoMovieScene::end()
{
	// デモムービーが再生されていたら
	if (false)
	{
		// デモムービーを停止する
	}
}
