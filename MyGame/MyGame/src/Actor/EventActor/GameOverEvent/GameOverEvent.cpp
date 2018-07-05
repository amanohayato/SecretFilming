#include "GameOverEvent.h"
#include "GameOverUfo.h"
#include "GameOverUfo.h"
#include"../../../Scene/Manager/GameDataManager.h"

#include"../../../Sound/Sound.h"
#include"../../Player/Player.h"

// ゲームオーバーイベントクラス
// 担当：Ho Siu Ki（何兆祺）
// 参考：Actor/EventActor/GameClearEvent.cpp

// コンストラクタ
GameOverEvent::GameOverEvent(IWorld* world, float goal_timer, const float goal_time, std::weak_ptr<EnemyBase> enemy) :
	goal_timer_(goal_timer), goal_time_(goal_time), enemy_(enemy)
{
	world_ = world;
}

// 初期化
void GameOverEvent::initialize()
{
	createUFOfunc_ = [&] {
		std::shared_ptr<GameOverUfo> ufo = std::make_shared<GameOverUfo>(world_, Vector3::Zero, Vector3{ world_->findActor("Enemy")->getPosition() });
		world_->addActor(ActorGroup::EVENT_ACTOR, ufo);
		ufo->setTarget(world_->findActor("Enemy"));
		ufo->begin();
	};
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().StopSE(SE_ID::RUN_SE);
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAMEOVER, DX_PLAYTYPE_LOOP);

	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PAUSE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
}

// 更新
void GameOverEvent::update(float delta_time)
{
	//InputChecker::GetInstance().InputStop();


	auto player=std::static_pointer_cast<Player>(world_->findActor("Player"));
	player->getFPSCamera().StartUpdate(camerapos_, Matrix::CreateRotationY(180));
	// 一回だけイベント用のアクターを生成
	if (goal_timer_ <= goal_time_)
	{
		createUFOfunc_();
		createUFOfunc_ = [] {};
	}

	// イベントに関係ないアクターを削除
	auto citizenlist = GameDataManager::getInstance().getCitizenList();	// 通行人
	auto carlist = GameDataManager::getInstance().getCarList();			// 車
	for (auto& at : citizenlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCitizenList(at.lock()->shared_from_this());	// 生きている市民のポインタを格納してるリストから自身を削除
	}
	for (auto& at : carlist)
	{
		at.lock()->dead();
		GameDataManager::getInstance().removeCarList(at.lock()->shared_from_this());		// 生きている車のポインタを格納してるリストから自身を削除
	}

	// イベントの処理
	

	// イベントタイマーを減算
	goal_timer_ -= delta_time;


	if (goal_timer_ <= 0.0f)
	{
		// BGMを止める
		Sound::GetInstance().StopBGM();

		InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::PAUSE_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
		InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);
	}
}

// 描画
void GameOverEvent::draw() const
{

}
