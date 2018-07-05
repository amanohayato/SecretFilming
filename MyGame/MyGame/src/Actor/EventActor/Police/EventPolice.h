#pragma once
#include"../../Actor.h"
#include"../../../Graphic/AnimationDx.h"
#include"../../Body/BoundingCapsule.h"
#include"../../../ID/EnumIDs.h"
//#include"../CityWalkPointChooser.h"
#include<map>
#include<list>


class EventPolice :public Actor {
private:
	enum class State {
		Walk,
		Idle,
		Down,
	};
	enum class Animation {
		Walk = 0,
		Idle = 1,
		Down = 2,
	};
	struct AnimStyle {
		AnimStyle(bool isloop, Animation anim) :isLoop(isloop), animation(anim) {

		}
		bool isLoop;
		Animation animation;
	};
public:
	EventPolice(IWorld* world, MODEL_ID id, int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void shadowDraw()const;
	//���S��
	virtual void end();
	//�ڐG��
	virtual void onCollide(Actor& other) override;

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

	void change_Animation(Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blendRate = 1.0f);
	void change_State(State state);
private:
	void idle(float deltaTime);
	void walk(float deltaTime);
	void down(float deltaTime);

	//�o�H����o�^����
	void setPath();
	//���g�̌����������I�ɑO�ɕ␳����
	void toForward();
private:
	AnimationDx animation_;//���f���y�уA�j���[�V�����̊Ǘ�

	MODEL_ID modelid_;//�g�p���f����ID

	State state_;//���

	int type_;

	std::vector<Vector3> path_;

	Vector3 prevPath_;
	bool extrudedflag_ = false;
	const std::map<State, AnimStyle> AnimConverter{//�X�e�[�g�ƃA�j���[�V�����̊֘A�t��
		{ State::Idle,AnimStyle{ false,Animation::Idle } },
	{ State::Walk,AnimStyle{ true,Animation::Walk } },
	{ State::Down,AnimStyle{ false,Animation::Down } }
	};
};