#include "CameraUI.h"
#include"../Graphic/Sprite.h"
#include"../World/IWorld.h"

CameraUI::CameraUI(IWorld* world):
	world_(world)
{
}

void CameraUI::initialize()
{
}

void CameraUI::update(float deltaTime)
{
	if (alpha_ < 0)
		alpha_up_ = true;
	if (alpha_ >= 1)
		alpha_up_ = false;
	if(alpha_up_ == false)
		alpha_ -= deltaTime*speed_;
	else
		alpha_ += deltaTime*speed_;
}

void CameraUI::draw() const
{
	if (!world_->isSS()) {
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CAMERAUI1,Vector2::Zero);
	}
	else {
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CAMERAUI2,Vector2::Zero);
	}
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_RT_PUSH, Vector2{1700,270}, Vector2::Zero, alpha_, Vector2(0.5f, 0.5f));
}
