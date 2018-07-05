#ifndef ENEMY_H_
#define ENEMY_H_

#include <map>
#include "../Actor.h"
#include "../../Graphic/AnimationDx.h"
#include "../Body/BoundingCapsule.h"
#include "../../ID/EnumIDs.h"
#include "EnemyMovePointChooser.h"

// �G�l�~�[�N���X�i�x�[�X�N���X�j
// ����ҁFHo Siu Ki�i�����Q�j
class Enemy : public Actor
{
private:
	enum class EnemyState
	{
		Idle,			// �Î~
		Move,			// �ړ�
		Kouban,			// ��ԃC�x���g
		Takoyakiya,     // �����Ă����C�x���g
		Alley,			// �H�n���ł̃C�x���g
		Crossroad,      // �����_�ł̃C�x���g
		VendingMachine, // ���̋@�ł̃C�x���g
		SmokingArea,    // �i�����ł̃C�x���g
		Sakanaya,        // �����C�x���g
		RandomEvent1,	// �����_���C�x���g1
		RandomEvent2,	// �����_���C�x���g2
		RandomEvent3,	// �����_���C�x���g3
		RandomEvent4	// �����_���C�x���g4
	};

	enum class EnemyAnimation
	{
		Idle = 0,			// �Î~
		Move = 1,			// �ړ�
		Kouban = 2,			// ��ԃC�x���g
		Takoyakiya = 3,     // �����Ă����C�x���g
		Alley = 4,			// �H�n���ł̃C�x���g
		Crossroad = 5,      // �����_�ł̃C�x���g
		VendingMachine = 6, // ���̋@�ł̃C�x���g
		SmokingArea = 7,    // �i�����ł̃C�x���g
		Sakanaya = 8,	    // �����C�x���g
		RandomEvent1 = 0,	// �����_���C�x���g1
		RandomEvent2 = 7,	// �����_���C�x���g2
		RandomEvent3 = 8,	// �����_���C�x���g3
		RandomEvent4 = 9	// �����_���C�x���g4
	};

	struct AnimStyle {
		AnimStyle(bool isloop, EnemyAnimation anim) :is_loop(isloop), animation(anim) { }
		bool is_loop;
		EnemyAnimation animation;
	};

public:
	// �R���X�g���N�^
	Enemy(IWorld* world, const Vector3& position, int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	// ������
	void initialize() override;
	// �X�V
	void update(float delta_time) override;
	// �`��
	void draw() const override;
	// �ڐG����
	void onCollide(Actor& other) override;
	// ���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

private:
	// ��Ԃ̕ύX
	void change_state(EnemyState state);
	// �A�j���[�V�����̕ύX
	void change_Animation(EnemyAnimation animID, float anim_frame = 0.0f, float anim_speed = 1.0f, bool is_loop = true, float blend_rate = 1.0f);
	// �Î~��Ԃ̏���
	void idle(float delta_time);
	// �ړ���Ԃ̏���
	void move(float delta_time);

	// ��Ԃł̃C�x���g
	void kouban(float delta_time);
	// �����Ă����ł̃C�x���g
	void takoyakiya(float delta_time);
	// �H�n���ł̃C�x���g
	void alley(float delta_time);
	// �����_�ł̃C�x���g
	void crossroad(float delta_time);
	// ���̋@�ł̃C�x���g
	void vending_machine(float delta_time);
	// �i�����ł̃C�x���g
	void smoking_area(float delta_time);
	// �����ł̃C�x���g
	void sakanaya(float delta_time);

	// �����_���C�x���g1
	virtual void random_event1(float delta_time);
	// �����_���C�x���g2
	virtual void random_event2(float delta_time);
	// �����_���C�x���g3
	virtual void random_event3(float delta_time);
	// �����_���C�x���g4
	virtual void random_event4(float delta_time);

private:
	AnimationDx animation_;			// �A�j���[�V����
	EnemyMovePointChooser chooser_;	// �ړ����W�w��
	EnemyState state_;				// �G�l�~�[�̏��
	float timer_{ 10.0f };			// �^�C�}�[

	// �G�l�~�[�̏�ԂƃA�j���[�V�����̊֘A�t��
	const std::map<EnemyState, AnimStyle> AnimConverter
	{
		{ EnemyState::Idle, AnimStyle{ true, EnemyAnimation::Idle } },
		{ EnemyState::Move, AnimStyle{ true, EnemyAnimation::Move } },
		{ EnemyState::Kouban, AnimStyle{ false, EnemyAnimation::Kouban } },
		{ EnemyState::Takoyakiya, AnimStyle{ false, EnemyAnimation::Takoyakiya } },
		{ EnemyState::Alley, AnimStyle{ false, EnemyAnimation::Alley } },
		{ EnemyState::Crossroad, AnimStyle{ false, EnemyAnimation::Crossroad } },
		{ EnemyState::VendingMachine, AnimStyle{ false, EnemyAnimation::VendingMachine } },
		{ EnemyState::SmokingArea, AnimStyle{ false, EnemyAnimation::SmokingArea } },
		{ EnemyState::Sakanaya, AnimStyle{ false, EnemyAnimation::Sakanaya } },
		{ EnemyState::RandomEvent1, AnimStyle{ false, EnemyAnimation::RandomEvent1 } },
		{ EnemyState::RandomEvent2, AnimStyle{ false, EnemyAnimation::RandomEvent2 } },
		{ EnemyState::RandomEvent3, AnimStyle{ false, EnemyAnimation::RandomEvent3 } },
		{ EnemyState::RandomEvent4, AnimStyle{ false, EnemyAnimation::RandomEvent4 } }
	};
};

#endif // !TEST_ENEMY_H_