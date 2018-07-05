#include "GamePlayScene.h"
#include "../../Actor/Actors.h"
#include "../../Graphic/Model.h"
#include "../../Field/FieldBase.h"
#include "../../Input/InputChecker.h"
#include "../../Define.h"
#include "../../Graphic/Sprite.h"
#include "../../Game/Time.h"
#include "../../UI/UIInclude.h"
#include "../../Sound/Sound.h"
#include "../../Actor/Object/HideObject.h"
#include "../../Actor/Object/Hide_InCamera.h"
#include "../../Camera/CaptureScreen.h"
#include "../Manager/GameDataManager.h"
#include "../../Actor/Enemy/Octopus.h"
#include "../../Actor/Object/Signal.h"
#include "../../Actor/Other/Confirm.h"
#include "../../Actor/Other/BgmChange.h"
#include "../../Actor/Other/IconControl.h"
#include "../../Event/EventManager/EventManager.h"
#include "../../Event/Event/Event.h"

#include "../SubScene/Menu/PauseMenu/PauseMunu.h"
#include "../SubScene/Menu/Option/Option.h"
#include "../SubScene/Menu/DecisionMenu/DecisionMenu.h"

#include "../../Actor/UIActor/MissionStart/MissionStart.h"

GamePlayScene::GamePlayScene():world_(),player_(nullptr)
{
	// 車生成クラスをワールドへ
	cagm_.setWorld(&world_);

	// 通行人生成クラスをワールドへ
	cigm_.setWorld(&world_);

	// サブシーンの種類の登録
	states_[SubSceneType::PAUSE_MENU] = std::make_shared<PauseMunu>();
	states_[SubSceneType::OPTION] = std::make_shared<Option>(SubSceneType::PAUSE_MENU);
	states_[SubSceneType::DECISION_MENU] = std::make_shared<DecisionMenu>(SceneType::SCENE_ENTRANCE, SubSceneType::PAUSE_MENU, SPRITE_ID::SPRITE_ASK_RETURN_TITLE);
}

void GamePlayScene::start()
{
	// ワールドクラスを初期化する
	world_.initialize();

	// 車生成クラスを初期化する
	cagm_.initialize();

	// 通行人生成クラスを初期化する
	cigm_.initialize();
	performance_.setWorld(&world_);
	
	// マップデータを読み込む
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");

	
	
	// プレイヤーをワールドとゲーム情報クラスに追加
	player_ = std::make_shared<Player>(&world_, Vector3{ 764,11.5,880 }, Matrix{ Matrix::Identity *  Matrix::CreateRotationX(0) * Matrix::CreateRotationY(90) });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);
	GameDataManager::getInstance().addAvoidTarget(player_);

	// 宇宙人をワールドとゲーム情報クラスに追加
	std::shared_ptr<Octopus> enemy = std::make_shared<Octopus>(&world_, Vector3{ 850,10,880 });
	world_.addActor(ActorGroup::ENEMY_ACTOR, enemy);
	GameDataManager::getInstance().addAvoidTarget(enemy);
	

	world_.addActor(ActorGroup::SIGNAL_ACTOR, std::make_shared<Signal>(&world_));//信号(仮)
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<Confirm>(&world_));//確定度ゲージ
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<BgmChange>(&world_));//BGM切り替えクラス
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<IconControl>(&world_));//アイコン切り替えクラス
	world_.addActor(ActorGroup::UI_ACTOR, std::make_shared<MissionStart>());//ミッションスタート


	auto action = std::make_shared<Action>(&world_, Vector2{ WINDOW_WIDTH*1.0f,WINDOW_HEIGHT*1.0f });
	world_.addUI(action);
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAME,DX_PLAYTYPE_LOOP);
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, 1.0f);

	// イベント管理クラスを追加
	mEventManager_ = new EventManager(world_);

	//mEventManager->AddEvent(EventManager::EventState::ZIHANKI_EVENT, new Event(mEventManager));
	//mEventManager->AddEvent(EventManager::EventState::KAIWA_EVENT, new Event(mEventManager));

	//mEventManager_->ChangeEvent(EventManager::EventState::ZIHANKI_EVENT);

	// ライト等の設定
	SetUseLighting(TRUE);
	SetLightEnable(TRUE);
	ChangeLightTypeDir(Vector3{ 0.0f,-1.0f,-0.5f });
	SetLightDifColor(GetColorF(0.5f, 0.5f, 0.5f, 0.5f));
	SetGlobalAmbientLight(GetColorF(0.2f, 0.2f, 0.2f, 0.2f));

	// ゲームの一時停止フラグを切る
	stopGame_ = false;

	Sound::GetInstance().SetEventListenerPos(player_->getPosition(), player_->getRotation().Forward());
	performance_.start();
	

}

void GamePlayScene::update(float deltaTime)
{

	Sound::GetInstance().SetEventListenerPos(player_->getPosition(), player_->getRotation().Forward());

	
	if (GameDataManager::getInstance().getGameStop() == true)
	{
		performance_.update(deltaTime);
		return;
	}

	if (stopGame_)
	{
		if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON))
		{
			stopGame_ = false;
		}

		if (curState_->isChangeScene())
		{
			if (curState_->nextScene() == SceneType::SCENE_GAMEPLAY)
			{
				curState_ = states_[SubSceneType::PAUSE_MENU];
				stopGame_ = false;
			}
			else
			{
				next_ = curState_->nextScene();
				isEnd_ = true;
			}
		}

		if (curState_->isChangeSubScene())
		{
			changeState(curState_->nextSubScene());
		}

		// エントランスシーンの状態の更新
		curState_->update(deltaTime);
		return;
	}

	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON))
	{
		// セレクトSEを再生
		Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

		changeState(SubSceneType::PAUSE_MENU);

		stopGame_ = true;
	}

	// スコアの値を取得しコンソールに仮出力
	auto score = CaptureScreen::getInstance().getScore();
	GameDataManager::getInstance().setScore(score);
	OutputDebugString(("合計スコア：" + std::to_string(score) + "\n").c_str());

	// バックボタンを入力するか、敵がゴール地点に辿り着いたら
	if (GameDataManager::getInstance().getEnemyGoal()||
		InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DEBUG_CLEAR_BUTTON))
	{
		// 終了処理を行う
		isEnd_ = true;
		auto score = CaptureScreen::getInstance().getScore();
		GameDataManager::getInstance().setScore(score);
		next_ = SceneType::SCENE_RESULT;
	}

	// 車生成クラスの更新
	cagm_.update(deltaTime);

	// 通行人生成クラスの更新
	cigm_.update(deltaTime);

	// ワールドの更新
	world_.update(deltaTime);

	// イベント管理クラスの更新
	mEventManager_->Update();
}

void GamePlayScene::draw() const
{

	// ワールドの描画
	world_.draw();

	// イベントマネージャーの描画
	mEventManager_->Draw();

	// タイマークラスのFPSの描画関数を呼ぶ
	Time::GetInstance().draw_fps();
}

void GamePlayScene::lateDraw()
{

	// ワールドの後描画
	world_.lateDraw();

	performance_.draw();

	if (stopGame_)
	{
		// サブシーンの描画
		curState_->draw();
	}
	
}

void GamePlayScene::end()
{
	// イベント管理クラスの削除
	delete mEventManager_;

	// ワールドの終了関数を呼ぶ
	world_.end();

	// BGMを止める
	Sound::GetInstance().StopBGM();
}

void GamePlayScene::changeState(SubSceneType next)
{
	if (curState_ != nullptr) curState_->end();
	curState_ = states_[next];
	curState_->start();
}
