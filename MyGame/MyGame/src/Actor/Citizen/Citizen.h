#pragma once
#include"../Actor.h"
//#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include"../../ID/EnumIDs.h"
#include "../../Graphic/AnimationOutSide.h"
#include<map>
#include<list>


class Citizen:public Actor {
private:
	enum class State {
		Idle,
		Walk,
		Down,
		Jump,
		Surprised,
		Dash,
	};
	enum class Animation {
		Idle = 0,
		Walk = 1,
		Surprised = 2,
		Surprised_Run = 3,
	};
	struct AnimStyle {
		AnimStyle(bool isloop, Animation anim) :isLoop(isloop), animation(anim) {

		}
		bool isLoop;
		Animation animation;
	};
public:
	Citizen(IWorld* world,MODEL_ID id,int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void shadowDraw()const override;
	//���S��
	virtual void end();
	//�ڐG��
	virtual void onCollide(Actor& other) override;

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

	void change_Animation(Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blendRate = 1.0f);
	void change_State(State state);
	void hit_Player(Vector3 & dir);
	void hit_Obj();
	bool Get_Path_Size_Half();
	int Get_Type();
private:
	void idle(float deltaTime);
	void walk(float deltaTime);
	void down(float deltaTime);
	void jump(float deltaTime);
	void dash(float deltaTime);
	void surprised(float deltaTime);

	void roadway();


	void avoid(float deltaTime);
	//�o�H����o�^����
	void setPath();
	void setLoop();
	//���g�̌����������I�ɑO�ɕ␳����
	void toForward();
private:
	//AnimationDx animation_;//���f���y�уA�j���[�V�����̊Ǘ�
	AnimationOutSide animation_;		// �A�j���[�V����

	MODEL_ID modelid_;//�g�p���f����ID

	State state_;//���
	
	int type_;

	std::list<Vector3> path_;

	Vector3 prevPath_;
	CsvReader roadway_;
	CsvReader crosswalk_;

	static const int player_distance_ = 200;
	static const int enemy_destance_ = 100;


	float count = 0;
	bool extrudedflag_ = false;
	const std::map<State, AnimStyle> AnimConverter{//�X�e�[�g�ƃA�j���[�V�����̊֘A�t��
		{State::Idle,AnimStyle{false,Animation::Idle}},
		{State::Walk,AnimStyle{true,Animation::Walk}},
		{State::Down,AnimStyle{false,Animation::Idle }},
	{ State::Jump,AnimStyle{ false,Animation::Idle } },
	{ State::Surprised,AnimStyle{ false,Animation::Surprised } },
		{ State::Dash,AnimStyle{ true,Animation::Surprised_Run } }
	};
	bool signal_ = false;//���s�җp�M���̏��
	bool breakflag = false;//��d���[�v�𔲂���p
	Vector3 beforpos_;//�O�̃|�W�V����
	Vector3 playerpos_;//�v���C���[�̈ʒu
	bool obj_hit_flag_ = false;
	int first_path_size_ = 0;
	
	float movepower_ = 0.5f;
	float dash_count_ = 0;

	Vector3 enemypos_{};
};