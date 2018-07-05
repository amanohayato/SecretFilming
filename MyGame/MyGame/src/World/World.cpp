#include "World.h"
#include"../ID/EnumIDs.h"
#include"../Actor/Actor.h"
#include"../Field/FieldBase.h"
#include"../Actor/Other/CameraActor.h"
#include"../Input/InputChecker.h"
#include"../Camera/CaptureScreen.h"
#include"../Define.h"
#include"../Field/Building/SendEventToEnemy.h"
#include"ObjectManager.h"
#include"../Actor/Player/Player.h"
#include"../Actor/TitleCamera/TitleCamera.h"
#include"../Graphic/ShadowMap.h"
#include"../Scene/Manager/GameDataManager.h"

#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
#define DOWN_SCALE_SCREEN_W	( WINDOW_WIDTH / DOWN_SCALE )	// ガウスフィルタを掛ける画像の横幅
#define DOWN_SCALE_SCREEN_H	( WINDOW_HEIGHT / DOWN_SCALE )	// ガウスフィルタを掛ける画像の縦幅

//#define NONE_SHADOW//影描画の停止

static constexpr float TdrawX_ = 200.0f;
static constexpr float TdrawY_ = 800.0f;

World::World()
{
	_makeScreenFunc = [&] {
		screen_ = MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT, FALSE);
		downScaleScreen_ = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
		gaussScreen_ = MakeScreen(DOWN_SCALE_SCREEN_W, DOWN_SCALE_SCREEN_H, FALSE);
	};
}

World::~World()
{
	DeleteGraph(screen_);
	DeleteGraph(downScaleScreen_);
	DeleteGraph(gaussScreen_);
}

void World::initialize()
{
	// 画面撮影クラスを初期化する
	CaptureScreen::getInstance().clear();
	// ゲーム情報クラスを初期化する
	GameDataManager::getInstance().initialize();

	eventList_.clear();
	//actors_.initialize();
	// ウェイポイントを読み込む
	walkMap_.initialize();
	addWalkPoint("res/Data/waypoint.csv", "res/Data/enemywalkedge.csv");
	worldManager_.initialize();
	worldManager_.setupWorld(this);
	uiManager_.initialize();
	phoneUIManager_.initialize();
	//camera_.reset();
	map_.initialize();
	map_.getWorld(this);//テスト用
	cam_.initialize();
	frame.initialize();
	drawFuncList_.clear();
	isCamera_ = false;
	isSS_ = false;

	_makeScreenFunc();
	_makeScreenFunc = [] {};

	point1.x = WINDOW_WIDTH / 4.0f;
	point1.y = WINDOW_HEIGHT / 4.0f;
	point2 = point1 * 3.0f;
	ssAmount_ = 0.0f;
	cameraAmount_ = 0.0f;
	mapAmount_ = 0.0f;
	//SS撮影関数を登録
	ssCapture_.Initialize();
	ssCapture_.Add([] {
		CaptureScreen::getInstance().capture();
		//CaptureScreen::getInstance().save();
	});
	ssCapture_.ToLast();


	textBox_.Init();
	textBox_.add("debug1.txt");
	textBox_.add("debug2.txt");
	textBox_.add("debug3.txt");
	textBox_.add("debug4.txt");
	textBox_.add("debug5.txt");
	textBox_.add("debug6.txt");
	textBox_.Start_Text();
	
}

void World::update(float deltaTime)
{
	//actors_.update(deltaTime);
	worldManager_.update(deltaTime);
	uiManager_.update(deltaTime);
	phoneUIManager_.update(deltaTime);
	frame.update(deltaTime);

	auto plyr = std::static_pointer_cast<Player>(findActor("Player"));
	if (plyr != nullptr)
	{
		isCamera_ = plyr->isCamera();
	}
	else
	{
		auto titleCamera = std::static_pointer_cast<TitleCamera>(findActor("TitleCamera"));
		isCamera_ = titleCamera->isCamera();
	}

	textBox_.Update();
	cam_.update(deltaTime);
	ssAmount_ += 0.05f;
	if (ssAmount_ > 1.0f) {
		isSS_ = false;
	}

	Player_State_ID psi;

	if (plyr != nullptr) psi = plyr->getStateType();

	constexpr float RATE = 0.05f;
	if (plyr != nullptr) {
		cameraAmount_ += (isCamera_	) ? RATE : -RATE;
		cameraAmount_ = MathHelper::Clamp(cameraAmount_, 0.0f, 1.0f);
		mapAmount_ += (psi == Player_State_ID::MapApp) ? RATE : -RATE;
		mapAmount_ = MathHelper::Clamp(mapAmount_, 0.0f, 1.0f);
	}
}
/*************************************************************************************************************************************************************************/
void World::draw() const
{
	if (cameraAmount_>0.01f) {
		CameraDraw();
		
		textBox_.Draw(Vector2{ TdrawX_,TdrawY_ });
		return;
	}
	if (mapAmount_ > 0.01f) {
		MapDraw();
		return;
	}
	Camera::GetInstance().Initialize();
	worldManager_.drawSkyBox();

	shadowmapDraw();

	uiManager_.draw();
	
	textBox_.Draw(Vector2{ TdrawX_,TdrawY_ });
}
void World::end()
{
}

void World::worldDraw()const {
	worldManager_.actorDraw();
	ssCapture_.Action();
	map_.draw();
}
void World::shadowmapDraw() const
{
#ifndef NONE_SHADOW
	ShadowMap::GetInstance().Begin(SHADOW_ID::GAME_SHADOW);
	shadowDraw();
	ShadowMap::GetInstance().End();
	ShadowMap::GetInstance().Enable(SHADOW_ID::GAME_SHADOW, 0);
	worldManager_.buildingDraw();
	ShadowMap::GetInstance().Disable(0);
	worldDraw();
#else
	worldManager_.buildingDraw();
	worldDraw();
#endif
}
void World::CameraDraw() const {
	// 描画先をカメラ画像にする
	SetDrawScreen(screen_);
	////画面のクリア
	ClearDrawScreen();
	//カメラ設定の適用
	Camera::GetInstance().Initialize();
	worldManager_.drawSkyBox();
	//ワールド要素を描画する
	shadowmapDraw();
	//画像の解像度を落とす
	GraphFilterBlt(screen_, downScaleScreen_, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
	//スクリーンショット関係
	if (isSS_)ssDraw();
	else FarstSSDraw();
	cam_.draw();
	constexpr int PixelWidth=16;// 使用ピクセル幅(8, 16, 32 の何れか)
	int BlurParam = (int)MathHelper::Lerp(0.0f,900.0f,MathHelper::Smoothstep(0.0f,1.0f,cameraAmount_));// ぼかしパラメータ(100 で約1ピクセル分の幅)(0～900)
	//画像にガウスぼかしを適用する
	GraphFilterBlt(downScaleScreen_, gaussScreen_, DX_GRAPH_FILTER_GAUSS, PixelWidth, BlurParam);
	//描画対象を裏画面に切り替える
	SetDrawScreen(DX_SCREEN_BACK);
	//画面のクリア
	ClearDrawScreen();
	//カメラ設定の適用
	Camera::GetInstance().Initialize();
	//ガウスぼかしを適用した画像を画面いっぱいに描画
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, gaussScreen_, FALSE);
	//カメラポジションの計算
	Vector2 lerp = Vector2::Lerp(Vector2(0.f, (float)WINDOW_HEIGHT), Vector2::Zero, MathHelper::Smoothstep(0.0f, 1.0f, cameraAmount_));
	//カメラ画像を描画
	DrawGraph((int)lerp.x, (int)lerp.y, screen_, FALSE);

	//カメラアプリ画像を描画
	//DrawExtendGraphF(point1.x, point1.y, point2.x, point2.y, screen_, FALSE);
}
void World::MapDraw() const
{
	// 描画先をカメラ画像にする
	SetDrawScreen(screen_);
	////画面のクリア
	ClearDrawScreen();
	//カメラ設定の適用
	Camera::GetInstance().Initialize();
	worldManager_.drawSkyBox();
	//ワールド要素を描画する
	shadowmapDraw();
	//画像の解像度を落とす
	GraphFilterBlt(screen_, downScaleScreen_, DX_GRAPH_FILTER_DOWN_SCALE, DOWN_SCALE);
	//スクリーンショット関係
	constexpr int PixelWidth = 16;// 使用ピクセル幅(8, 16, 32 の何れか)
	int BlurParam = (int)MathHelper::Lerp(0.0f, 900.0f, MathHelper::Smoothstep(0.0f, 1.0f, mapAmount_));// ぼかしパラメータ(100 で約1ピクセル分の幅)(0～900)
																										   //画像にガウスぼかしを適用する
	GraphFilterBlt(downScaleScreen_, gaussScreen_, DX_GRAPH_FILTER_GAUSS, PixelWidth, BlurParam);
	//描画対象を裏画面に切り替える
	SetDrawScreen(DX_SCREEN_BACK);
	//画面のクリア
	ClearDrawScreen();
	//カメラ設定の適用
	Camera::GetInstance().Initialize();
	//ガウスぼかしを適用した画像を画面いっぱいに描画
	DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, gaussScreen_, FALSE);
	//カメラポジションの計算
	//Vector2 lerp = Vector2::Lerp(Vector2(0, WINDOW_HEIGHT), Vector2::Zero, MathHelper::Smoothstep(0.0f, 1.0f, cameraAmount_));



	//カメラ画像を描画
	//DrawGraph(lerp.x, lerp.y, screen_, FALSE);

	//カメラアプリ画像を描画
	//DrawExtendGraphF(point1.x, point1.y, point2.x, point2.y, screen_, FALSE);

}
void World::ssDraw()const {
	Vector2 drawPosition_ = Vector2::Lerp(Vector2::Zero, Vector2(WINDOW_WIDTH - WINDOW_WIDTH * 0.125f, WINDOW_HEIGHT - WINDOW_HEIGHT * 0.125f), MathHelper::Smoothstep(0.0f, 1.0f, ssAmount_));
	Vector2 drawScale = Vector2::Lerp(Vector2::One, Vector2(0.125f, 0.125f), MathHelper::Smoothstep(0.0f, 1.0f, ssAmount_));
	CaptureScreen::getInstance().drawFarst(drawPosition_, Vector2::Zero,1.0f,drawScale);
	frame.draw(drawPosition_, drawScale);

}
void World::FarstSSDraw()const {
	CaptureScreen::getInstance().drawFarst(Vector2(WINDOW_WIDTH - WINDOW_WIDTH * 0.125f, WINDOW_HEIGHT - WINDOW_HEIGHT * 0.125f), Vector2::Zero, 1.0f, Vector2(0.125f, 0.125f));
}
void World::shadowDraw() const
{
	worldManager_.shadowDraw();

}

void World::lateDraw()
{
	for (auto& f : drawFuncList_) {
		f();
	}
	drawFuncList_.clear();

}

void World::handleMessage(EventMessage message, void * param)
{
}

void World::addActor(ActorGroup group, const ActorPtr & actor)
{
	//actors_.addActor(group, actor);
	worldManager_.addActor(group, actor);
}

void World::addUI(const UIPtr & ui)
{
	uiManager_.add(ui);
}

void World::addPhoneUI(const UIPtr & ui)
{
	phoneUIManager_.add(ui);
}

void World::loadMap(const std::string & pointfilename,const std::string& mapfilename)
{
	map_.load(pointfilename,mapfilename);
}

void World::addWalkPoint(const std::string & pointfilename, const std::string & mapfilename)
{
	walkMap_.load(pointfilename, mapfilename);
}

//void World::addCamera(const std::shared_ptr<CameraActor> & cameraActor)
//{
//	camera_ = cameraActor;
//	actors_.addActor(ActorGroup::ETCETERA_ACTOR, cameraActor);
//
//}

ActorPtr World::findActor(const std::string & name)
{
	return worldManager_.findActor(name);
}

void World::findActors(ActorGroup group,const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	worldManager_.findActor(group,name, actorList);
}

int World::getActorCount(ActorGroup group) const
{
	return worldManager_.getSize(group);
}

void World::sendMessage(EventMessage message, void * param)
{
	worldManager_.handleMessage(message, param);
}

std::shared_ptr<Field> World::getFieldOnly()
{
	return worldManager_.getField();
}

std::shared_ptr<Skybox> World::getSkybox()
{
	return worldManager_.getSkybox();
}

TextBox & World::getTextBox()
{
	return textBox_;
}
CityMap & World::getCityMap()
{
	return map_;
}

WalkGraph & World::getWalkMap()
{
	return walkMap_;
}

void World::addDrawFunction(std::function<void()> func)
{
	drawFuncList_.push_back(func);
}


void World::screenShot(int score)
{
	isSS_ = true;
	ssAmount_ = 0.0f;
	frame.initialize();
	//ssCapture_.NumReset();
	ssCapture_.Initialize();
	ssCapture_.Add([score] {
		CaptureScreen::getInstance().capture(score);
	    CaptureScreen::getInstance().mGraph();
	});

}

bool World::isSS()
{
	return isSS_;
}

bool World::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	return worldManager_.hitToLine(firstPos, secondPos);
}

std::list<std::shared_ptr<BuildingBase>>& World::getBuildings()
{
	return worldManager_.getObjManager().lock()->getBuildings().get();
}

float World::getMapAmount() const { return mapAmount_; }

float World::getCameraAmount() const
{
	return cameraAmount_;
}

std::list<EventPoint> World::getEventList()
{
	return eventList_;
}

void World::addEventList(EventPoint evp)
{
	eventList_.push_back(evp);
}

//std::weak_ptr<CameraActor> World::getCamera() const
//{
//	return camera_;
//}
