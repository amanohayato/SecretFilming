#include "ShutterFrame.h"
#include"../Graphic/Sprite.h"
#include"../Math/MathHelper.h"
#include"../World/IWorld.h"


ShutterFrame::ShutterFrame(IWorld * world):
	world_(world)
{
}

void ShutterFrame::initialize()
{
	amount = 1.0f;
}

void ShutterFrame::update(float deltaTime)
{
	alpha = MathHelper::Lerp(0.0f, 1.0f, MathHelper::Smoothstep(0.0f, 1.0f, amount));
	if (world_->isSS()) {
		amount -= 0.07f;
	}
	else {
		amount = 1.0f;
	}
}

void ShutterFrame::draw(Vector2& position,Vector2& size) const
{
	if (world_->isSS()) {
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_FRAME, position, Vector2::Zero, alpha, size);
	}
}
