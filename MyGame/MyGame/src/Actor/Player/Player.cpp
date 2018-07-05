#include "Player.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../../Field/Building/BuildingBase.h"
#include"../Other/CameraActor.h"
#include"../../Field/FieldBase.h"
#include"../../Graphic/AnimLoader.h"
#include"../../Graphic/Sprite.h"
#include"../../ID/EnumIDs.h"
#include"../../Define.h"
#include"../Other/CameraActor.h"
#include"../../Sound/Sound.h"
#include"Base/FPSCamera.h"
#include"State\StateIncludeh.h"
#include"../PhoneApp//SmartPhone.h"


Player::Player(IWorld* world, const Vector3& position, const IBodyPtr& body) :
	Actor(world, "Player", position, body)
{
	//回転行列初期化
	rotation_ = Matrix::Identity;
	fpsCam_.initialize(rotation_);

}

Player::Player(IWorld * world, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body) :
	Actor(world, "Player", position, rotation, body)
{
	fpsCam_.initialize(rotation_);
}

void Player::initialize()
{
	roadway_.load("res/Data/roadway.csv");
	// スマホの機能のアクターを作成、追加
	std::shared_ptr<SmartPhone> smartPhone = std::make_shared<SmartPhone>(world_, shared_from_this());
	smartPhone->initialize();
	addChild(smartPhone);


	state_ = std::make_shared<Player_Idle>(shared_from_this());

	//状態の開始
	state_->start();

	arm_.start(shared_from_this());
}

void Player::update(float deltaTime)
{

	beforpos_ = position_;
	//状態の更新
	state_->update(deltaTime);
	arm_.update(deltaTime);

	//回転行列の更新
	cameraRotation_ = fpsCam_.getRotation();
	rotation_ = Matrix::CreateRotationY(-Matrix::Angle(cameraRotation_).y);

	velocity_ += Vector3::Up * state_->getGravity();
	position_ += velocity_;
	velocity_ *= velocityMultPower;
	if (velocity_.Length() < 0.01f) {
		velocity_ = 0.0f;
	}

	//壁と床の当たり判定
	collision();
	//車道判定
	roadway();

	if ((InputChecker::GetInstance().KeyTriggerDown(Operation_Type::HIDE_BUTTON) &&
		(state_->getState() == Player_State_ID::Dash || state_->getState() == Player_State_ID::Idle || state_->getState() == Player_State_ID::Event_After)) && !collide) {
		//状態の遷移
		change_State(Player_State_ID::Event_Before);
		int r = GetRand(180) - 90;
		MODEL_ID model = (GetRand(9) != 0) ? MODEL_ID::MODEL_ARM_2 : MODEL_ID::MODEL_ARM_4;
		arm_.change_arm(model, shared_from_this(), Matrix::CreateRotationY(Matrix::Angle(rotation_).y + (float)r));
		state_->setObjct(position_, Matrix::Identity *  Matrix::CreateRotationX(20) * Matrix::CreateRotationY(Matrix::Angle(rotation_).y + (float)r));
	}
	if (state_->getNextState() != Player_State_ID::Null) {
		change_State(state_->getNextState());
	}

	collide = false;
}

void Player::draw() const
{
	arm_.draw();
	//DebugDraw::DebugDrawFormatString(500, 500, GetColor(255, 255, 255), "player:%.2f,%.2f,%.2f", position_.x, position_.y, position_.z);
	//DebugDraw::DebugDrawFormatString(500, 550, GetColor(255, 255, 255), "player:%.2f,%.2f,%.2f",fpsCam_.getRotation().Rotation().x, Matrix::Angle(fpsCam_.getRotation()).y, Matrix::Angle(fpsCam_.getRotation()).z);
	//DebugDraw::DebugDrawFormatString(500, 450, GetColor(255, 255, 255), "state:%d", state_->getState());
}

void Player::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Player, (void*)&hitdir);
}

void Player::receiveMessage(EventMessage message, void * param)
{
	switch (message)
	{
	case EventMessage::Hit_Car:
		hit(*(Vector3*)param);
		break;
	case EventMessage::Hit_Bullet:
		break;
	case EventMessage::Hide_Object:
		break;
	case EventMessage::Hide_InCamera:
		hide_InCamera(*(BuildingBase*)param);
		break;
	case EventMessage::Hit_Enemy:
		hit(*(Vector3*)param);
	case EventMessage::Stop_Player:
		change_State(Player_State_ID::Idle);
	default:
		break;
	}
}

Player_State_ID Player::getStateType() const
{
	return state_->getState();
}


FPSCamera& Player::getFPSCamera()
{
	return fpsCam_;
}

Player_arm & Player::getArm()
{
	return arm_;
}


bool Player::change_State(Player_State_ID state) {
	//同じ状態には遷移しない
	if (state_->getState() == state) return false;
	//状態の終了
	state_->end();
	//状態の繊維
	state_ = getState(state);
	//状態の開始
	state_->start();
	return true;
}

std::shared_ptr<PlayerState> Player::getState(Player_State_ID state)
{
	std::shared_ptr<PlayerState> state_;
	switch (state)
	{
	case Player_State_ID::Idle:
		state_ = std::make_shared<Player_Idle>(shared_from_this());
		break;
	case Player_State_ID::Dash:
		state_ = std::make_shared<Player_Dash>(shared_from_this());
		break;
	case Player_State_ID::Fall:
		state_ = std::make_shared<Player_Fall>(shared_from_this());
		break;
	case Player_State_ID::SetUp:
		state_ = std::make_shared<Player_SetUp>(shared_from_this());
		break;
	case Player_State_ID::Event_Before:
		state_ = std::make_shared<Player_Event_Before>(shared_from_this());
		break;
	case Player_State_ID::EventAction:
		state_ = std::make_shared<Player_EventAction>(world_, shared_from_this());
		break;
	case Player_State_ID::Event_After:
		state_ = std::make_shared<Player_Event_After>(shared_from_this());
		break;
	case Player_State_ID::Launch:
		state_ = std::make_shared<Player_Launch>(shared_from_this());
		break;
	case Player_State_ID::MapApp:
		state_ = std::make_shared<Player_MapApp>(shared_from_this());
		break;
	case Player_State_ID::ActionReset:
		state_ = std::make_shared<Player_ActionReset>(shared_from_this());
		break;
	default:
		state_ = std::make_shared<Player_Idle>(shared_from_this());
		break;
	}
	return state_;
}


void Player::hide_InCamera(BuildingBase& object)
{
	//アクション出来るか
	if (object.isPlay()) {
		Vector3 dir = position_ - world_->findActor("Enemy")->getPosition();
		hit(dir);
		return;
	}
	if (state_->getState() != Player_State_ID::Idle && state_->getState() != Player_State_ID::Dash) return;

	collide = true;

	PlayerStatus status = object.getStatus();
	object.message(EventMessage::Emission);
	//状態がIdleとDashの場合のときにのみR２を押されたらイベントの開始
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::HIDE_BUTTON)) {
		//イベント情報の取得
		type_ = object.getEvent();
		//状態の遷移
		change_State(Player_State_ID::Event_Before);
		if(object.getEvent() == EventType::EVENT_VENDING) arm_.change_arm(MODEL_ID::MODEL_ARM_1, shared_from_this(), status.getRotation());
		else arm_.change_arm(MODEL_ID::MODEL_ARM_3, shared_from_this(), status.getRotation());
		//プレイヤーの位置とリセット時の向きを渡
		state_->setObjct(status.getPosition() + (Vector3::Up * position_.y), status.getRotation());
	}
}

void Player::hit(Vector3& dir)
{
	if (state_->getState() != Player_State_ID::Launch || !isAction_) {
		Vector3 dir_ = Vector3::Normalize(dir);
		//アクターからプレイヤーの方向に移動
		velocity_ = Vector3::Up * 7.0f + Vector3{ dir_.x,0.f,dir_.z } * 2.0f;
		change_State(Player_State_ID::Launch);
		collide = true;
	}
}

void Player::collision()
{
	//ぶつかったか
	Vector3 result;
	//壁とぶつけてから
	if (field(result)) {
		position_ = result;
	}
	//床との接地判定
	if (floor(result)) {
		state_->setFloor(true);
		position_ = result + rotation_.Up() *(body_->length()*0.5f + body_->radius());
	}
	else state_->setFloor(false);

}
void Player::roadway()
{
	//車道判定
	for (int i = 0; i < roadway_.rows(); i++) {
		if (position_.x > roadway_.getf(i, 0) && position_.x < roadway_.getf(i, 1) && position_.z > roadway_.getf(i, 2) && position_.z < roadway_.getf(i, 3))
		{
			float x0, x1, z2, z3;
			x0 = std::abs(roadway_.getf(i, 0) - position_.x);
			x1 = std::abs(roadway_.getf(i, 1) - position_.x);
			z2 = std::abs(roadway_.getf(i, 2) - position_.z);
			z3 = std::abs(roadway_.getf(i, 3) - position_.z);
			std::list<float> minimum = { x0,x1,z2,z3 };
			minimum.sort();

			if (minimum.front() == x0) position_.x = roadway_.getf(i,0);
			else if (minimum.front() == x1) position_.x = roadway_.getf(i, 1);
			if (minimum.front() == z2) position_.z = roadway_.getf(i,2);
			else if (minimum.front() == z3) position_.z = roadway_.getf(i, 3);
		}
	}

}