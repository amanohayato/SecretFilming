#include "ConversationState.h"
#include <DxLib.h>

ConversationState::ConversationState(IWorld & world) {
	world_ = &world;
}

void ConversationState::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//�C�x���g��
	enemyBase_.lock()->set_is_event(true);
	// �A�j���[�V�����Đ�
	//enemyBase_->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::FallDown), false);
	count_ = 0.0f;
}

void ConversationState::Update()
{
	auto blue = 0.4f*MathHelper::Abs((float)std::sin(count_));
	count_ += 0.1f;

	// ���F������
	MV1SetMaterialEmiColor(enemyBase_.lock()->get_animation().getModelHandle(), 0, GetColorF(0.6f, 0.6f, blue, 1.0f));

	//�A�j���[�V�����I��������ǂ��� 
	if (count_ > 10) {
		MV1SetMaterialEmiColor(enemyBase_.lock()->get_animation().getModelHandle(), 0, GetColorF(0.0f, 0.0f, 0.0f, 1.0f));
		isEnd_ = true;
	}
}

void ConversationState::Draw() const
{
}

bool ConversationState::IsEnd() const
{
	return isEnd_;
}

void ConversationState::End()
{
}

RandomEvent ConversationState::Next() const
{
	return RandomEvent::LookAround_State;
}
