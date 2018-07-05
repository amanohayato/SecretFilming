#include "Action.h"
#include"../World/IWorld.h"
#include"../Actor/Actor.h"
#include"../Math/MathHelper.h"
#include"../Graphic/Sprite.h"

Action::Action(IWorld * world, const Vector2 & position) :
	UI("Action", position), world_(world)
{
}

void Action::initialize()
{
}

void Action::update(float deltaTime)
{
	is_Action = world_->findActor("Player")->isAction();
	if (is_Action) {
		alpha = MathHelper::Lerp(0.0f, 1.0f, MathHelper::Smoothstep(0.0f, 1.0f, amount));
		if (amount > 1.0f) {
			amount = 1.0f;
		}
		else if (amount < 1.0f) {
			amount += 0.04f;
		}
	}
	else {
		alpha = MathHelper::Lerp(1.0f, 0.0f, MathHelper::Smoothstep(1.0f, 0.0f, amount));
		if (amount < 0.0f) {
			amount = 0.0f;
		}
		else if (amount > 0.0f) {
			amount -= 0.04f;
		}
	}
}

void Action::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_ACTION, Vector2::Zero, alpha);
}
