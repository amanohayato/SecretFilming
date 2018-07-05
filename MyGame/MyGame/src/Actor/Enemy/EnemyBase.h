#ifndef ENEMY_BASE_H_
#define ENEMY_BASE_H_

#include <map>
#include "../Actor.h"
#include "../../Graphic/AnimationOutSide.h"
#include "../Body/BoundingCapsule.h"
#include "../../ID/EnumIDs.h"
#include "EnemyMovePointChooser.h"
#include "../../Field/Building/SendEventToEnemy.h"
#include "../../Event/RandomEvent/RandomEventManager/RandomEventManager.h"
#include "EnemyCap.h"
#include "../EventActor/EventEnemy/EnemyHatManager/EnemyHatManager.h"
#include"../UIActor/TextActor.h"

// �G�l�~�[�x�[�X�N���X
// �S���FHo Siu Ki�i�����Q�j

class EnemyBase : public Actor
{
	friend class EnemyCap;

public:
	// �G�l�~�[�̏��
	enum class EnemyState
	{
		Idle,				// �Î~
		Move,				// �ړ�
		Escape,				// ����
		Goal,				// �S�[�����B
		PoliceBox,			// ��ԃC�x���g
		Takoyakiya,			// �����Ă����C�x���g
		BackStreet1,		// �H�n���ł̃C�x���g1
		BackStreet2,		// �H�n���ł̃C�x���g2
		Junction,			// �����_�ł̃C�x���g
		VendingMachine,		// ���̋@�ł̃C�x���g
		SmokingArea,		// �i�����ł̃C�x���g
		FishMonger,			// �����C�x���g
		RandomEvent1,		// �����_���C�x���g1
		RandomEvent2,		// �����_���C�x���g2
		RandomEvent3,		// �����_���C�x���g3
		//PreAction,		// �\������
		Stop,				// ��~
		DiscoveryStart,		// �v���C���[�����J�n
		Discovery,			// �v���C���[����
		DiscoveryEnd,		// �v���C���[�����I��
		Aware,				// �x��
		LookBack,			// �U��Ԃ�
		ToPlayer,			// �U��Ԃ�
	};
	// �G�l�~�[�̃A�j���[�V����
	enum class EnemyAnimation
	{
		Idle = 0,			// �Î~
		Move = 1,			// �ړ�
		Escape = 2,			// ����
		Angry = 5,			// �{��
		Goal = 0,			// �S�[���C�x���g
		PoliceBox = 4,		// ��ԃC�x���g
		Takoyakiya = 5,     // �����Ă����C�x���g
		BackStreet1 = 6,	// �H�n���ł̃C�x���g1
		BackStreet2 = 4,	// �H�n���ł̃C�x���g2
		Junction = 3,		// �����_�ł̃C�x���g
		VendingMachine = 8, // ���̋@�ł̃C�x���g
		VendingMachine_Poi = 9,
		SmokingArea = 10,   // �i�����ł̃C�x���g
		FishMonger = 4,	    // �����C�x���g
		RandomEvent1 = 12,	// �����_���C�x���g1
		RandomEvent2 = 12,	// �����_���C�x���g2
		RandomEvent3 = 12,	// �����_���C�x���g3
		PreAction = 11,		// ���O����
		Stop = 0,			// ��~
		Aware = 11,			// �x��
		Hat = 12,			// �X�q����
		Me_Mogaki = 3,		// �ڂ̂�����
		Nod = 12,
		LOOK_UP = 13,		// UFO�����グ��
		UDEKUMI = 14,		// �r�g
		Manhole_Rescue = 7,	// ���X�L���[		
		Manhole_Fall = 16,	// �}���z�[������
		FallDown = 17,      // �]��
		RisingHat = 18,     // �N���オ��
		Gaze1 = 19,			// �̂����J�n
		Gaze2 = 20,			// �̂�������
		Gaze3 = 21,			// �̂����I��
		Memory_Delete = 22,	// �L������
		Kaiwa = 23,         // ��b
		LookBack = 24,		// �U��Ԃ�
		LookLeft = 25,
		LookRight = 26,
	};

	// �A�j���[�V�����̍Đ��ݒ�
	struct AnimStyle
	{
		AnimStyle(bool isloop, EnemyAnimation anim) :is_loop(isloop), animation(anim) { }
		bool is_loop;
		EnemyAnimation animation;
	};

public:
	// �R���X�g���N�^
	EnemyBase(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	virtual ~EnemyBase();
	// ������
	void initialize() override;
	// �X�V
	void update(float delta_time) override;
	// �`��
	void draw() const override;
	void shadowDraw() const override;
	// �ڐG����
	virtual void onCollide(Actor& other) override;
	// ���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param = nullptr) override;
	// �C�x���g�̎擾
	void get_event();
	// ��]�s��̎擾
	Matrix& get_rotation();
	// �A�j���[�V�����N���X�̎擾
	AnimationOutSide& get_animation();
	// �C�x���g�t���O�̐ݒ�
	EnemyState get_state()const { return state_; }
	void set_is_event(bool is_event);
	bool get_is_event()const;

	std::list<EventPoint>& GetEventPoints();
	//�S���҈ȊO�ǉ���
	/*******************************************************/
	float get_awareness()const;
	void set_awareness(const float &awareness);//�N���A�C�x���g���o�p
	std::string get_ui_target()const;
	int getBaseScore()const;
	void setBaseScore(int score);
	Vector3 getHeadPos()const;
	void on_Barrier(ActorPtr target, ActorPtr enemy, bool isStop = false);//�o���A
	std::array<Vector3, 3> getHeadVertex()const;

	bool isPathEnd()const;

	//�ǂ������߂��p�X����Ԃ�
	std::vector<Vector3> GetNearPath(const std::vector<Vector3>& p1, const std::vector<Vector3>& p2);


	std::vector<Vector3> getPath()const;

	std::shared_ptr<EnemyHatManager> GetEnemyHat();

	void setNextEvent();

	void fallcap();
	void pickcap();
	void wearcap();
	/*******************************************************/
protected:
	// ��Ԃ̕ύX
	void change_state(EnemyState state);
	// �A�j���[�V�����̕ύX
	void change_animation(EnemyAnimation animID, float anim_frame = 0.0f, float anim_speed = 1.0f, bool is_loop = true, float blend_rate = 1.0f);
	// �Î~��Ԃ̏���
	void idle(float delta_time);
	// �ړ���Ԃ̏���
	void move(float delta_time);
	// ������Ԃ̏���
	void escape(float delta_time);
	// �S�[���C�x���g����
	void goal(float delta_time);
	// ��~��Ԃ̏���
	void stop(float delta_time);
	//�v���C���[�����J�n�̏���
	void discoveryStart(float delta_time);
	//�v���C���[�������̏���
	void discovery(float delta_time);
	//�v���C���[�����I���̏���
	void discoveryEnd(float delta_time);
	// �x����Ԃ̏���
	void aware(float delta_time);
	// �U��Ԃ鏈��
	void look_back(float delta_time);
	// �U��Ԃ鎞�Ԃ̐ݒ�
	void set_look_back_time();

	void to_player(float deltaTime);

	// �v���[���[�������鋗�����ɂ��邩
	bool is_player_in_viewing_distance();
	// �v���[���[�������鎋��p���ɂ��邩
	bool is_player_in_viewing_angle();
	// �v���[���[�������邩
	bool can_see_player();
	// �v���[���[�����̊p�x�����߂�
	float player_position_angle() const;

	// ���̖ړI�n�ւ̌o�H�T��
	void next_destinstion();

	// �x���x����
	void awareness(float delta_time);
	// �x���Q�[�W�̕\��
	void show_awareness();

	// ��Ԃł̃C�x���g����
	virtual void police_box(float delta_time);
	// �����Ă����ł̃C�x���g����
	virtual void takoyakiya(float delta_time);
	// �H�n���ł̃C�x���g1����
	virtual void back_street_1(float delta_time);
	// �H�n���ł̃C�x���g2����
	virtual void back_street_2(float delta_time);
	// �����_�ł̃C�x���g����
	virtual void junction(float delta_time);
	// ���̋@�ł̃C�x���g����
	virtual void vending_machine(float delta_time);
	// �i�����ł̃C�x���g����
	virtual void smoking_area(float delta_time);
	// �����ł̃C�x���g����
	virtual void fish_monger(float delta_time);

	// �����_���C�x���g1����
	virtual void random_event1(float delta_time);
	// �����_���C�x���g2����
	virtual void random_event2(float delta_time);
	// �����_���C�x���g3����
	virtual void random_event3(float delta_time);

	//���O���쏈��
	//virtual void pre_action(float delta_time);

	//�ړI�C�x���g�����̃C�x���g�ɐݒ�
	void setNextEventPath();
	void setNextEventPath_Reset();

	void setText(const std::string& text);
protected:

	std::shared_ptr<EnemyHatManager> mEnemyHatManager;
	AnimationOutSide animation_;		// �A�j���[�V����
	EnemyState state_;					// �G�l�~�[�̏��

	std::weak_ptr<Actor> player_;		// �v���[���[�̎Q��
	float viewing_distance_{ 120.0f };	// ��������
	float viewing_angle_{ 40.0f };		// ����p�i�x�j

	float timer_{ 10.0f };				// �^�C�}�[�i�b�j
	float normal_speed_{ 0.0f };		// �ʏ펞�̈ړ����x
	float escape_speed_{ 0.0f };		// �������̈ړ����x

	float look_back_timer_;				// �U��Ԃ�^�C�}�[

	float escape_timer_{ 10.0f };		// ������ԃ^�C�}�[
	float goal_timer_{ 0.0f };			// �S�[���^�C�}�[�i�Q�[���I�[�o�[�V�[���Ɉڍs�܂ł̎��ԁj
	float goal_time_{ 10.0f };      //�Q�[���I�[�o�[�V�[���Ɉڍs����܂ł̎��Ԃ������Œ�`����

	float awareness_{ 0.0f };			// �x���x
	float aware_up_rate_{ 0.2f };		// �x���x�㏸��
	float aware_down_rate_{ 0.2f };		// �x���x������
	float awareness_timer_{ 0.0f };		// �x���x�����^�C�}�[
	float aware_state_timer_{ 0.0f };	// �x����ԃ^�C�}�[

	bool is_goal_{ false };				// �S�[���ɓ��B������
	bool is_event_{ false };			// �C�x���g��Ԃł��邩
	bool is_aware_{ false };			// �x�����ł��邩
	bool is_performance_{ false }; //�N���A���o�O���o�������邩

	float delta_time_ = 10.0f;

	Vector3 player_position_{ Vector3::Zero };

	std::weak_ptr<EnemyCap> cap_;

	Vector3 head_pos{ Vector3::Zero };//���̈ʒu
	std::array<Vector3, 3> head_vertex{ Vector3::Zero,Vector3::Zero,Vector3::Zero };//���̃T�C�Y
	std::function<void()> change_state_;
	std::function<void()> last_walk_path_;
	// �ړI�n���X�g
	std::list<EventPoint> event_points_;
	// ���̖ړI�n�ւ̌o�H
	std::vector<Vector3> path_;

	int score_{ 0 };

	// ****************************************
	// ��ΐ��O�ǉ���
	// �x�����̃��b�Z�[�W��\�����邩�t���O
	bool displayWarningText_{ true };

	// �����_���C�x���g�̔����t���O
	bool randomEventFlag_{ true };
	// ****************************************

	// �G�l�~�[�̏�ԂƃA�j���[�V�����̊֘A�t��
	const std::map<EnemyState, AnimStyle> AnimConverter
	{
		{ EnemyState::Idle, AnimStyle{ true, EnemyAnimation::Idle } },						// �Î~
		{ EnemyState::Move, AnimStyle{ true, EnemyAnimation::Move } },						// �ړ�
		{ EnemyState::Escape, AnimStyle{ true, EnemyAnimation::Escape } },					// ����
		{ EnemyState::Goal, AnimStyle{ false, EnemyAnimation::Goal } },						// �S�[���C�x���g
		{ EnemyState::PoliceBox, AnimStyle{ false, EnemyAnimation::PoliceBox } },			// ��ԃC�x���g
		{ EnemyState::Takoyakiya, AnimStyle{ false, EnemyAnimation::Takoyakiya } },			// �����Ă����C�x���g
		{ EnemyState::BackStreet1, AnimStyle{ false, EnemyAnimation::BackStreet1 } },		// �H�n���C�x���g1
		{ EnemyState::BackStreet2, AnimStyle{ false, EnemyAnimation::BackStreet2 } },		// �H�n���C�x���g2
		{ EnemyState::Junction, AnimStyle{ false, EnemyAnimation::Junction } },				// �����_�C�x���g
		{ EnemyState::VendingMachine, AnimStyle{ false, EnemyAnimation::VendingMachine } },	// ���̋@�C�x���g
		{ EnemyState::SmokingArea, AnimStyle{ false, EnemyAnimation::SmokingArea } },		// �i�����C�x���g
		{ EnemyState::FishMonger, AnimStyle{ false, EnemyAnimation::FishMonger } },			// �����C�x���g
		{ EnemyState::RandomEvent1, AnimStyle{ false, EnemyAnimation::RandomEvent1 } },		// �����_���C�x���g1
		{ EnemyState::RandomEvent2, AnimStyle{ false, EnemyAnimation::RandomEvent2 } },		// �����_���C�x���g2
		{ EnemyState::RandomEvent3, AnimStyle{ false, EnemyAnimation::RandomEvent3 } },		// �����_���C�x���g3
		//{ EnemyState::PreAction, AnimStyle{ false, EnemyAnimation::PreAction } },			// ���O����
		{ EnemyState::Stop, AnimStyle{ true, EnemyAnimation::Stop } },						// ��~
		{ EnemyState::DiscoveryStart, AnimStyle{ false, EnemyAnimation::Gaze1 } },			// �v���C���[�����J�n
		{ EnemyState::Discovery, AnimStyle{ true, EnemyAnimation::Gaze2 } },				// �v���C���[����
		{ EnemyState::DiscoveryEnd, AnimStyle{ false, EnemyAnimation::Gaze3 } },			// �v���C���[�����I��
		{ EnemyState::Aware, AnimStyle{ true, EnemyAnimation::Aware } },					// �x��
		{ EnemyState::LookBack, AnimStyle{ false, EnemyAnimation::LookBack } },				// �U��Ԃ�
		{ EnemyState::ToPlayer, AnimStyle{ true, EnemyAnimation::Move } },						// �ړ�
	};

private:
	std::shared_ptr<RandomEventManager>eventManager_;

	std::weak_ptr<TextActor> _text{};
};

#endif // !ENEMY_BASE_H_