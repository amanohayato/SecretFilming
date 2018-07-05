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

// ���[���h���ۃC���^�[�t�F�[�X
class World:public IWorld {
public:
	World();
	~World();
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
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
	//���b�Z�[�W��M
	void handleMessage(EventMessage message, void* param);
	// �A�N�^�[�̒ǉ�
	virtual void addActor(ActorGroup group, const ActorPtr& actor)override;
	virtual void addUI(const UIPtr& ui)override;
	virtual void addPhoneUI(const UIPtr& ui)override;
	//�ԓ��̓ǂݍ���
	void loadMap(const std::string& filename, const std::string& mapfilename);
	//�����̒ǉ�
	void addWalkPoint(const std::string& pointfilename, const std::string& mapfilename);
	//void addCamera(const std::shared_ptr<CameraActor> & cameraActor);
	// �A�N�^�[�̌���
	virtual ActorPtr findActor(const std::string& name)override;
	// �A�N�^�[�̕�������
	virtual void findActors(ActorGroup group,const std::string& name, std::list<std::weak_ptr<Actor>>& actorList)override;
	//�A�N�^�[�̐����擾
	virtual int getActorCount(ActorGroup group)const override;
	// ���b�Z�[�W�̑��M
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

	//�B�e
	virtual void screenShot(int score = 0) override;

	virtual bool isSS()override;

	// �֐��� ��ŕς��܂�
	virtual bool hitToLine(Vector3 firstPos, Vector3 secondPos) override;

	virtual std::list<std::shared_ptr<BuildingBase>>& getBuildings() override;

	virtual float getMapAmount()const;
	virtual float getCameraAmount()const;

private:
	UIManager uiManager_{};
	UIManager phoneUIManager_{};
	WorldContentManager worldManager_{};
	CityMap map_{};//���H�}�b�v
	WalkGraph walkMap_{};//�����}�b�v���X�g
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
	int downScaleScreen_;//�𑜓x�𗎂Ƃ����X�N���[��
	int gaussScreen_;//�K�E�X�ڂ�����K�p�����X�N���[��
	std::list<std::function<void()>> drawFuncList_;

	// �Q�[�����ŋN����C�x���g�̃��X�g
	std::list<EventPoint> eventList_;

	std::function<void()> _makeScreenFunc;
};
