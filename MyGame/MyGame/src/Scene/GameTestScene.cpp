#include "GameTestScene.h"
#include"../Actor/Actors.h"
#include"../Graphic/Model.h"
#include"../Field/FieldBase.h"
#include"../Input/InputChecker.h"
#include"../Define.h"
#include"../Graphic/Sprite.h"
#include"../Game/Time.h"
#include"../UI/UIInclude.h"
#include"../Sound/Sound.h"
#include"../Actor/Object/HideObject.h"
#include"../Actor/Object/Hide_InCamera.h"

 GameTestScene:: GameTestScene() :world_(), player_(nullptr)
{
}

void  GameTestScene::start()
{
	world_.initialize();

	//world_.setField(std::make_shared<FieldBase>(Model::GetInstance().GetHandle(MODEL_ID::MODEL_STAGE), Model::GetInstance().GetHandle(MODEL_ID::MODEL_SKYBOX)));
	world_.loadMap("res/Data/map.csv", "res/Data/pathmap.csv");
	world_.addWalkPoint("res/Data/wp1.csv", "res/Data/we1.csv");
	world_.addWalkPoint("res/Data/wp2.csv", "res/Data/we2.csv");

	player_ = std::make_shared<Player>(&world_, Vector3{ 0,10.0f,0 });
	world_.addActor(ActorGroup::PLAYER_ACTOR, player_);

	//world_.addActor(ActorGroup::CITIZEN_ACTOR, std::make_shared<Citizen>(&world_, Vector3{ 1000.0f,10.0f,-50.0f }, MODEL_ID::MODEL_CITIZEN_USAUSA, 0));
	//world_.addActor(ActorGroup::CITIZEN_ACTOR, std::make_shared<Citizen>(&world_, Vector3{ 380.0f,10.0f,875.0f }, MODEL_ID::MODEL_CITIZEN_USAUSA, 1));
	
	world_.addActor(ActorGroup::ENEMY_ACTOR, std::make_shared<HideObject>(&world_, Vector3{ 100.0f, 0.0f,0.0f }+Vector3::Up*10.0f));
	world_.addActor(ActorGroup::ENEMY_ACTOR, std::make_shared<Hide_InCamera>(&world_, Vector3{ -100.0f,0.0f,0.0f }+Vector3::Up*10.0f));

	//auto point = std::make_shared<CheckPoint>(&world_, Vector3{ 0.0f,5.0f,10.0f });
	//world_.addActor(ActorGroup::POINT_ACTOR , point);
	
	auto camera = std::make_shared<CameraActor>(&world_, player_->getPosition());
	//world_.addCamera(camera);
	camera->setTarget(player_);


	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GAME, DX_PLAYTYPE_LOOP);
}

void  GameTestScene::update(float deltaTime)
{
	world_.update(deltaTime);

	// ポーズボタンでゲーム終了していたのでそのように適応しました（by 大槻）
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::PAUSE_BUTTON)) {
		isEnd_ = true;
		next_ = SceneType::SCENE_ENTRANCE;
	}

	//cc.update(deltaTime);
}

void  GameTestScene::draw() const
{
	world_.draw();

	Time::GetInstance().draw_fps();
	//DrawCircleGauge(50, 50, 100.0f, Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_FLOATGAUGE));
}

void  GameTestScene::lateDraw()
{
	world_.lateDraw();
}

void  GameTestScene::end()
{
	Sound::GetInstance().StopBGM();
}
