#include "NoticedLine.h"

// �C�Â����N���X
// �S���FHo Siu Ki�i�����Q�j

// �R���X�g���N�^
NoticedLine::NoticedLine(ActorPtr target)
	: Actor(nullptr, "NoticedLine", target->getPosition()), target_(target)
{ }

// ������
void NoticedLine::initialize()
{

}

// �X�V
void NoticedLine::update(float delta_time)
{
	if (timer_ <= 0.0f)
	{
		isDead_ = true;
	}

	timer_ -= delta_time;
}

// �`��
void NoticedLine::draw() const
{
	if (target_==nullptr)	return;

	constexpr float upPower = 15.f;
	auto drawPos = target_->getPosition() + Vector3::Up*upPower;
	constexpr float size = 10.f;

	Model::GetInstance().Draw2D(MODEL_ID::SPRITE_NOTICED_LINE, drawPos, 0, size);
}