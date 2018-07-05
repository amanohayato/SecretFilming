#include "Enemy.h"
#include"../../Graphic/Model.h"

// �e�X�g�p�G�l�~�[�N���X
// ����ҁFHo Siu Ki�i�����Q�j

// �R���X�g���N�^
Enemy::Enemy(IWorld* world, const Vector3& position, int type, const IBodyPtr& body)
	: Actor(world, "Enemy", position, body), animation_(), chooser_(world, position, type)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	// change_state(EnemyState::Move);		// ��Ԃ�ݒ�
	change_state(EnemyState::RandomEvent1);
}

// ������
void Enemy::initialize()
{
}

// �X�V
void Enemy::update(float delta_time)
{
	animation_.Update(1.0f);	// �A�j���[�V�������X�V

	// ��Ԃɉ����ď������s��
	switch (state_)
	{
	case Enemy::EnemyState::Idle:
		idle(delta_time);
		break;
	case Enemy::EnemyState::Move:
		move(delta_time);
		break;
	case Enemy::EnemyState::Kouban:
		kouban(delta_time);
		break;
	case Enemy::EnemyState::Takoyakiya:
		takoyakiya(delta_time);
		break;
	case Enemy::EnemyState::Alley:
		alley(delta_time);
		break;
	case Enemy::EnemyState::Crossroad:
		crossroad(delta_time);
		break;
	case Enemy::EnemyState::VendingMachine:
		vending_machine(delta_time);
		break;
	case Enemy::EnemyState::SmokingArea:
		smoking_area(delta_time);
		break;
	case Enemy::EnemyState::Sakanaya:
		sakanaya(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent1:
		random_event1(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent2:
		random_event2(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent3:
		random_event3(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent4:
		random_event4(delta_time);
		break;
	default:
		break;
	}
}

// �`��
void Enemy::draw() const
{
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
	body_->transform(getPose())->draw();
}

// �ڐG����
void Enemy::onCollide(Actor & other)
{

}

// ���b�Z�[�W�̎�M
void Enemy::receiveMessage(EventMessage message, void * param)
{

}

// ��Ԃ̕ύX
void Enemy::change_state(EnemyState state)
{
	// �G�l�~�[�̏�Ԃ�ύX
	state_ = state;
	// �A�j���[�V������ύX
	change_Animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).is_loop);

	// ��ԕω���̏���
	switch (state_)
	{
	case Enemy::EnemyState::Idle:
		timer_ = 10.0f;
		break;
	case Enemy::EnemyState::Move:
		chooser_.choose_goal();
		break;
	case Enemy::EnemyState::Kouban:
		break;
	case Enemy::EnemyState::Takoyakiya:
		break;
	case Enemy::EnemyState::Alley:
		break;
	case Enemy::EnemyState::Crossroad:
		break;
	case Enemy::EnemyState::VendingMachine:
		break;
	case Enemy::EnemyState::SmokingArea:
		break;
	case Enemy::EnemyState::Sakanaya:
		break;
	case Enemy::EnemyState::RandomEvent1:
		timer_ = 10.0f;
		break;
	case Enemy::EnemyState::RandomEvent2:
		break;
	case Enemy::EnemyState::RandomEvent3:
		break;
	case Enemy::EnemyState::RandomEvent4:
		break;
	default:
		break;
	}
}

// �A�j���[�V�����̕ύX
void Enemy::change_Animation(EnemyAnimation animID, float anim_frame, float anim_speed, bool is_loop, float blend_rate)
{
	animation_.ChangeAnim((int)animID, anim_frame, anim_speed, is_loop);
}

// �Î~��Ԃ̏���
void Enemy::idle(float delta_time)
{
	timer_ -= delta_time;

	if (timer_ <= 0.0f)
	{
		change_state(EnemyState::Move);
	}
}

// �ړ���Ԃ̏���
void Enemy::move(float delta_time)
{
	float power = 3.0f;
	bool isEnd;

	Vector3 toTargetPosition = (chooser_(position_, isEnd) - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f*power*power);
	position_ += rotation_.Forward()*0.3f*power;

	if (isEnd)
	{
		change_state(EnemyState::Idle);
	}
}

// ��Ԃł̃C�x���g
void Enemy::kouban(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �����Ă����ł̃C�x���g
void Enemy::takoyakiya(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �H�n���ł̃C�x���g
void Enemy::alley(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �����_�ł̃C�x���g
void Enemy::crossroad(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// ���̋@�ł̃C�x���g
void Enemy::vending_machine(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �i�����ł̃C�x���g
void Enemy::smoking_area(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �����ł̃C�x���g
void Enemy::sakanaya(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// �����_���C�x���g1
void Enemy::random_event1(float delta_time)
{
	timer_ -= delta_time;

	if (timer_ <= 0.0f) {
		change_state(EnemyState::RandomEvent2);
	}
}

// �����_���C�x���g2
void Enemy::random_event2(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent3);
	}
}

// �����_���C�x���g3
void Enemy::random_event3(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent4);
	}
}

// �����_���C�x���g4
void Enemy::random_event4(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent1);
	}
}