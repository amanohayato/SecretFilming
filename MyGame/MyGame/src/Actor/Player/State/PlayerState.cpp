#include "PlayerState.h"
#include"../../../Sound/Sound.h"
#include"../../../Input/InputChecker.h"
#include"../../../World/IWorld.h"
#include"../../../Scene/Manager/GameDataManager.h"
#include"../Player.h"

PlayerState::PlayerState(ActorPtr player) :
	player_(player),fpsCam_(static_cast<Player*>(player.get())->getFPSCamera())
{
}

PlayerState::PlayerState(IWorld * world, ActorPtr player) :
	world_(world), player_(player), fpsCam_(static_cast<Player*>(player.get())->getFPSCamera())
{
}

void PlayerState::start()
{
}

void PlayerState::update(float deltaTime)
{
}

void PlayerState::end()
{
}

void PlayerState::input_to_move(float deltaTime)
{
	fpsCam_.getsens() = GameDataManager::getInstance().getCameraSens();

	// 前フレーム地面に設置していたら重力の力をゼロにする
	if (prevfloor_)gravity_ = 0.0f;
	// コントローラーのスティックの傾き具合を取得
	Vector2 stickDirection = InputChecker::GetInstance().Stick();

	// もしスティックの傾き具合が0.2以下だったら
	if (stickDirection.Length() <= 0.2f) {


		// 再生しているダッシュSEインスタンスを停止する
		Sound::GetInstance().StopSE(SE_ID::RUN_SE);

		// この関数を終了
		return;
	}

	// ダッシュSEインスタンスを再生する
	Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::RUN_SE);
	if (getState() == Player_State_ID::Dash) {
		//ダッシュSEを再生
		Sound::GetInstance().SetRate(SE_ID::RUN_SE,50000);
	}
	else {
		Sound::GetInstance().ReSetRate(SE_ID::RUN_SE);
	}
	// 次にプレイヤーの座標を変更するのに使用する方向・速度の値を用意 
	Vector3 frameVelocity = Vector3::Zero;

	// コントローラーのスティックの傾きと自身の回転方向を使う
	frameVelocity = (Vector3{ stickDirection.x, 0.0f, stickDirection.y } * moveSpeed_) * fpsCam_.getRotation();

	// １フレームの経過時間分の補正をかける
	frameVelocity *= deltaTime;

	// 自身の座標の値に方向・速度の値を適用（※ここで直に position の値に適用して大丈夫かな？）
	player_->getPosition() += frameVelocity;
	player_->getPosition().z = MathHelper::Clamp(player_->getPosition().z,160.0f,GameDataManager::getInstance().getMapSize().y);
}

void PlayerState::setFloor(bool prevfloor)
{
	prevfloor_ = prevfloor;
}

Player_State_ID PlayerState::getState() const
{
	return state_;
}

Player_State_ID PlayerState::getNextState() const
{
	return nextState_;
}

FPSCamera PlayerState::getFPSCam() const
{
	return fpsCam_;
}


void PlayerState::setObjct(const Vector3 & position, const Matrix & rotation)
{
	objPositionStr_ = position;
	objRotation_ = rotation;
	fpsCam_.SetRotation(rotation);
}

float PlayerState::getGravity() const
{
	return gravity_;
}

bool PlayerState::isCamera() const
{
	return isCamera_;
}

bool PlayerState::isAction() const
{
	return isAction_;
}

void PlayerState::setIsWatch(const bool& isWatch)
{
	isWatch_ = isWatch;
}

bool PlayerState::getIsWatch() const
{
	return isWatch_;
}

void PlayerState::setFPSCam(FPSCamera cam)
{
	fpsCam_ = cam;
}