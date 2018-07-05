#include "NoticedLine.h"

// 気づき線クラス
// 担当：Ho Siu Ki（何兆祺）

// コンストラクタ
NoticedLine::NoticedLine(ActorPtr target)
	: Actor(nullptr, "NoticedLine", target->getPosition()), target_(target)
{ }

// 初期化
void NoticedLine::initialize()
{

}

// 更新
void NoticedLine::update(float delta_time)
{
	if (timer_ <= 0.0f)
	{
		isDead_ = true;
	}

	timer_ -= delta_time;
}

// 描画
void NoticedLine::draw() const
{
	if (target_==nullptr)	return;

	constexpr float upPower = 15.f;
	auto drawPos = target_->getPosition() + Vector3::Up*upPower;
	constexpr float size = 10.f;

	Model::GetInstance().Draw2D(MODEL_ID::SPRITE_NOTICED_LINE, drawPos, 0, size);
}