#pragma once

#include"../Actor/ActorPtr.h"
#include"../UI/UIPtr.h"

#include "../Field/Building/BuildingPtr.h"
#include "../Field/WorldContentManager/WorldContentManager.h"
#include"../Graphic/TextBox.h"

#include <string>
#include<list>
#include<functional>

enum class ActorGroup;
enum class EventMessage;
class CameraActor;
class CityMap;
class WalkGraph;
class FadeSprite;
struct EventPoint;


// ワールド抽象インターフェース
class IWorld {
public:
	// 仮想デストラクタ
	virtual ~IWorld() {}
	// アクターの追加
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	//UIの追加
	virtual void addUI(const UIPtr& ui) = 0;
	virtual void addPhoneUI(const UIPtr& ui) = 0;
	// アクターの検索
	virtual ActorPtr findActor(const std::string& name) = 0;
	// アクターの複数検索
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) = 0;
	//アクターの数を取得
	virtual int getActorCount(ActorGroup group)const = 0;
	// メッセージの送信
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;

	virtual std::shared_ptr<Field> getFieldOnly() = 0;
	virtual std::shared_ptr<Skybox> getSkybox() = 0;
	virtual TextBox& getTextBox() = 0;

	//virtual std::weak_ptr<CameraActor> getCamera()const = 0;
	virtual CityMap& getCityMap() = 0;
	virtual WalkGraph& getWalkMap() = 0;
	virtual std::list<EventPoint> getEventList()=0;
	virtual void addEventList(EventPoint evp) = 0;
	//撮影
	virtual void screenShot(int score=0) = 0;
	virtual void addDrawFunction(std::function<void()> func) = 0;

	virtual bool hitToLine(Vector3 firstPos, Vector3 secondPos) = 0;

	virtual bool isSS() = 0;

	virtual std::list<std::shared_ptr<BuildingBase>>& getBuildings() = 0;

	virtual float getMapAmount()const = 0;
	virtual float getCameraAmount()const = 0;
;
};
