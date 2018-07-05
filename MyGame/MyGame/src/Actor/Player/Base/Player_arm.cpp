#include "Player_arm.h"
#include"../../../Graphic/AnimationDx.h"
#include"../../../Graphic/Model.h"
#include"../Player.h"
#include<memory>

Player_arm::Player_arm()
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ARM_2));
}

void Player_arm::start(ActorPtr player)
{
	playerptr_ = player;
	auto player_ = std::static_pointer_cast<Player>(playerptr_);
	position_ = player_->getPosition() - player_->getRotation().Up() * 0.5f;
	rotation_ = Matrix::CreateRotationY(-Matrix::Angle(player_->getRotation()).y) * Matrix::CreateRotationY(180);
	isArm_ = true;
}

void Player_arm::update(float deltaTime)
{
	move(deltaTime);
	animation_.Update(MathHelper::Sign(deltaTime)*0.5f);
}

void Player_arm::draw() const
{
	if (isArm_) animation_.Draw(Matrix(rotation_).Translation(position_));
}

void Player_arm::change_arm(MODEL_ID name, ActorPtr player,Matrix rotation)
{
	playerptr_ = player;
	playerRot =  Matrix::CreateRotationY(Matrix::Angle(rotation).y) * Matrix::CreateRotationY(-180);
	animation_.SetHandle(Model::GetInstance().GetHandle(name));
	if (name == MODEL_ID::MODEL_ARM_1 || name == MODEL_ID::MODEL_ARM_3) isAction_ = true;
	else isAction_ = false;
}

void Player_arm::isArm(bool isArm)
{
	isArm_ = isArm;
}

bool Player_arm::isAction() const
{
	return isAction_;
}

void Player_arm::move(float deltaTime)
{
	auto player_ = std::static_pointer_cast<Player>(playerptr_);
	if (player_->getStateType() == Player_State_ID::EventAction) {
		amount = MathHelper::Clamp(amount + 0.04f, 0.0f, 1.0f);
		rot = Matrix::CreateRotationX(MathHelper::Lerp(90.0f, 10.0f, MathHelper::Smoothstep(0, 1, amount)));
		Vector3 rightMove;
		if(isAction_) rightMove = playerRot.Right() * 1.2f;
		else rightMove = Vector3::Zero;
		pos = rightMove - playerRot.Forward() * MathHelper::Lerp(-2.0f, 1.0f, MathHelper::Smoothstep(0, 1, amount)) - playerRot.Up() * MathHelper::Lerp(2.0f, 0.0f, MathHelper::Smoothstep(0, 1, amount));
		position_ = player_->getPosition() + pos;
		if (amount >= 0.99f) {
			position_ += player_->getRotation().Up() * MathHelper::Sin(fmodf(timer_ * 100.0f, 360.0f)) / 5.0f;
			timer_ += deltaTime;
		}
		rotation_ = rot * playerRot;
		isArm_ = true;
	}
	else if (player_->getStateType() == Player_State_ID::Event_After) {
		amount = MathHelper::Clamp(amount - 0.04f, 0.0f, 1.0f);
		rot = Matrix::CreateRotationX(MathHelper::Lerp(-90.0f, 10.0f, MathHelper::Smoothstep(0, 1, amount)));
		Vector3 rightMove;
		if (isAction_) rightMove = playerRot.Right() * 1.2f;
		else rightMove = Vector3::Zero;
		pos = rightMove - playerRot.Forward() * MathHelper::Lerp(-2.0f, 1.0f, MathHelper::Smoothstep(0, 1, amount)) - playerRot.Up() * MathHelper::Lerp(2.0f, 0.0f, MathHelper::Smoothstep(0, 1, amount));
		position_ = player_->getPosition() + pos;
		rotation_ = rot * playerRot;
		isArm_ = true;
	}
	else{
		isArm_ = false;
		amount = 0.0f;
		timer_ = 0.0f;
	}
}
