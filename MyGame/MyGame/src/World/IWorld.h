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


// ���[���h���ۃC���^�[�t�F�[�X
class IWorld {
public:
	// ���z�f�X�g���N�^
	virtual ~IWorld() {}
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor) = 0;
	//UI�̒ǉ�
	virtual void addUI(const UIPtr& ui) = 0;
	virtual void addPhoneUI(const UIPtr& ui) = 0;
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name) = 0;
	// �A�N�^�[�̕�������
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList) = 0;
	//�A�N�^�[�̐����擾
	virtual int getActorCount(ActorGroup group)const = 0;
	// ���b�Z�[�W�̑��M
	virtual void sendMessage(EventMessage message, void* param = nullptr) = 0;

	virtual std::shared_ptr<Field> getFieldOnly() = 0;
	virtual std::shared_ptr<Skybox> getSkybox() = 0;
	virtual TextBox& getTextBox() = 0;

	//virtual std::weak_ptr<CameraActor> getCamera()const = 0;
	virtual CityMap& getCityMap() = 0;
	virtual WalkGraph& getWalkMap() = 0;
	virtual std::list<EventPoint> getEventList()=0;
	virtual void addEventList(EventPoint evp) = 0;
	//�B�e
	virtual void screenShot(int score=0) = 0;
	virtual void addDrawFunction(std::function<void()> func) = 0;

	virtual bool hitToLine(Vector3 firstPos, Vector3 secondPos) = 0;

	virtual bool isSS() = 0;

	virtual std::list<std::shared_ptr<BuildingBase>>& getBuildings() = 0;

	virtual float getMapAmount()const = 0;
	virtual float getCameraAmount()const = 0;
;
};
