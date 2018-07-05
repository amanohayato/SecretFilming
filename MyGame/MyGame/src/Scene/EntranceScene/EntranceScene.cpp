#include "EntranceScene.h"
#include "../../Sound/Sound.h"
#include "../../Graphic/Sprite.h"
#include "../../Define.h"
#include <DxLib.h>
#include "../../Actor/Actors.h"
#include "../../Actor/TitleCamera/TitleCamera.h"
#include "../../Actor/TitleActor/TitleUfo/TitleUfoFactory.h"

#include"../SubScene/Title/Title.h"
#include"../SubScene/Menu/MainMenu/MainMenu.h"
#include"../SubScene/Menu/Option/Option.h"

EntranceScene::EntranceScene()
{
	// 車生成クラスをワールドへ
	cagm_.setWorld(&world_);

	// 通行人生成クラスをワールドへ
	cigm_.setWorld(&world_);

	subScenes_[SubSceneType::TITLE] = std::make_shared<Title>();
	subScenes_[SubSceneType::MAIN_MENU] = std::make_shared<MainMenu>();
	subScenes_[SubSceneType::OPTION] = std::make_shared<Option>(SubSceneType::MAIN_MENU);
}

void EntranceScene::start()
{
	// 経過時間をクリア
	elapsedTime_ = 0;

	// ワールドクラスを初期化する
	world_.initialize();

	// マップデータを読み込む
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");

	// ウェイポイントを読み込む
	world_.addWalkPoint("res/Data/waypoint.csv", "res/Data/enemywalkedge.csv");

	// タイトル用回転カメラをワールドに追加
	titleCamera_ = std::make_shared<TitleCamera>(&world_, Vector3::Zero);
	world_.addActor(ActorGroup::UI_ACTOR, titleCamera_);

	// タイトル用UFO作成クラスを追加
	titleUfoFactory_ = std::make_shared<TitleUfoFactory>(&world_);
	world_.addActor(ActorGroup::UI_ACTOR, titleUfoFactory_);

	// 基本の初期化関数を呼ぶ
	baseInit();

	// 次のシーンをゲームプレイ中に変える
	next_ = SceneType::SCENE_GAMEPLAY;

	// エントランスシーンのBGMを鳴らす
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_TITLE, DX_PLAYTYPE_LOOP);

	// 現在の状態をタイトルにする
	changeState(SubSceneType::TITLE);

	transitionsAnimeType_ = TransitionsAnimeType::FadeAnimation;
}

void EntranceScene::update(float deltaTime)
{
	// 経過時間の更新
	elapsedTime_ += deltaTime;

	// 何かしらのキー入力があるかオプションシーンだったら、経過時間をゼロにする
	if (InputChecker::GetInstance().KeyStateDown(Operation_Type::ANY_BUTTON) || curSubScene_ == subScenes_[SubSceneType::OPTION])
	{
		elapsedTime_ = 0;
	}

	// ワールドの更新
	world_.update(deltaTime);

	// デモムービーシーンへの移行条件が整っていたら
	if (elapsedTime_ > goDemoSceneTime_)
	{
		// 次のシーンを“デモムービーシーン”にセットする
		//next_ = SceneType::SCENE_DEMOMOVIE;

		// このシーンの終了条件をOnにする
		//isEnd_ = true;
	}

	// 
	if (curSubScene_->isChangeScene())
	{
		 
		next_ = curSubScene_->nextScene();

		// このシーンの終了条件をOnにする
		isEnd_ = true;
	}

	// 
	if (curSubScene_->isChangeSubScene())
	{
		changeState(curSubScene_->nextSubScene());
	}

	isGameEnd_ = curSubScene_->isGameEnd();

	// エントランスシーンの状態の更新
	curSubScene_->update(deltaTime);
}

void EntranceScene::draw() const
{
	// ワールドの描画
	world_.draw();

	// エントランスシーンの状態の描画
	curSubScene_->draw();
}

void EntranceScene::lateDraw()
{
	// ワールドの後描画
	world_.lateDraw();
}

void EntranceScene::end()
{
	// ワールドの終了関数を呼ぶ
	world_.end();

	Sound::GetInstance().StopBGM();
}

void EntranceScene::changeState(SubSceneType next)
{
	if (curSubScene_ != nullptr) curSubScene_->end();
	curSubScene_ = subScenes_[next];
	curSubScene_->start();
}
