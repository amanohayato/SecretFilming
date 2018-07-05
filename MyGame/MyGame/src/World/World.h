#pragma once
#include"IWorld.h"
#include"../Actor/ActorManager.h"
#include"../UI/UIManager.h"
#include "../Field/WorldContentManager/WorldContentManager.h"
#include"../Field/CityMap.h"
#include"../Field/WalkGraph.h"
#include"../Method/MethodTimer.h"
#include "../Field/Building/SendEventToEnemy.h"
#include"../UI/CameraUI.h"
#include"../UI/ShutterFrame.h"

// ワールド抽象インターフェース
class World:public IWorld {
public:
	World();
	~World();
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw()const;
	void end();

	void ssDraw()const;
	void FarstSSDraw()const;
	void shadowDraw()const;
	void worldDraw()const;
	void shadowmapDraw()const;
	void CameraDraw()const;
	void MapDraw()const;
	void lateDraw();
	//メッセージ受信
	void handleMessage(EventMessage message, void* param);
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor)override;
	virtual void addUI(const UIPtr& ui)override;
	virtual void addPhoneUI(const UIPtr& ui)override;
	//車道の読み込み
	void loadMap(const std::string& filename, const std::string& mapfilename);
	//歩道の追加
	void addWalkPoint(const std::string& pointfilename, const std::string& mapfilename);
	//void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name)override;
	// アクターの複数検索
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList)override;
	//アクターの数を取得
	virtual int getActorCount(ActorGroup group)const override;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr)override;

	virtual std::shared_ptr<Field> getFieldOnly() override;
	virtual std::shared_ptr<Skybox> getSkybox() override;
	virtual TextBox& getTextBox() override;

	virtual CityMap& getCityMap()override;
	virtual WalkGraph& getWalkMap()override;
	//virtual std::weak_ptr<CameraActor> getCamera()const override;
	virtual void addDrawFunction(std::function<void()> func)override;
	virtual std::list<EventPoint> getEventList()override;
	virtual void addEventList(EventPoint evp)override;

	//撮影
	virtual void screenShot(int score = 0) override;

	virtual bool isSS()override;

	// 関数名 後で変えます
	virtual bool hitToLine(Vector3 firstPos, Vector3 secondPos) override;

	virtual std::list<std::shared_ptr<BuildingBase>>& getBuildings() override;

	virtual float getMapAmount()const;
	virtual float getCameraAmount()const;

private:
	UIManager uiManager_{};
	UIManager phoneUIManager_{};
	WorldContentManager worldManager_{};
	CityMap map_{};//道路マップ
	WalkGraph walkMap_{};//歩道マップリスト
	//std::weak_ptr<CameraActor> camera_{};
	bool isCamera_{ false };
	bool isSS_{ false };
	TextBox textBox_{2};
	CameraUI cam_{ this };
	ShutterFrame frame{ this };
	Vector2 point1{ 0.0f,0.0f };
	Vector2 point2{ 0.0f,0.0f };
	MethodTimer ssCapture_{};
	float ssAmount_{ 0.0f };
	float cameraAmount_{ 0.0f };
	float mapAmount_{ 0.0f };
	int screen_;
	int downScaleScreen_;//解像度を落としたスクリーン
	int gaussScreen_;//ガウスぼかしを適用したスクリーン
	std::list<std::function<void()>> drawFuncList_;

	// ゲーム内で起こるイベントのリスト
	std::list<EventPoint> eventList_;

	std::function<void()> _makeScreenFunc;
};
