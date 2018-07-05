#include "EventPolice.h"
#include"../../../Graphic/Model.h"
#include"../../../Graphic/DebugDraw.h"
#include"../../../Field/WalkGraph.h"
#include"../../../Scene/Manager/GameDataManager.h"
#include"../../Citizen/WalkPathReader.h"



static constexpr float FOV = 30.0f;
static constexpr float MAX_AVOID_SPACE = 33.0f;
EventPolice::EventPolice(IWorld * world, MODEL_ID id, int type, const IBodyPtr & body) :
	Actor(world, "EventPolice", Vector3::Zero, body), animation_(), modelid_(id), state_(State::Idle), type_(type)
{
	//chooser_.setPoint(position_);
	animation_.SetHandle(Model::GetInstance().GetHandle(id));

	//path_ = WalkPathReader::getInstance().getWalkList(type_);
	//position_ = path_.front();
}

void EventPolice::initialize()
{
	change_State(State::Walk);
	setPath();
}

void EventPolice::update(float deltaTime)
{
	animation_.Update(MathHelper::Sign(deltaTime)*0.5f);
	switch (state_)
	{
	case EventPolice::State::Idle:
		idle(deltaTime);
		break;
	case EventPolice::State::Walk:
		walk(deltaTime);
		break;
	case EventPolice::State::Down:
		down(deltaTime);
		break;
	default:
		break;
	}
}

void EventPolice::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));

	//body_->transform(getPose())->draw();

	for (auto& i : path_) {
		DebugDraw::DebugDrawSphere3D(i, 3.f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	}
	/*
	if(type_==0)
	DebugDraw::DebugDrawFormatString(500, 400, GetColor(255, 255, 255), "%f,%f", position_.x, position_.z);
	*/

}

void EventPolice::shadowDraw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));

}

void EventPolice::end()
{
}

void EventPolice::onCollide(Actor & other)
{
	//Vector3 hitdir = (other.getPosition() - position_);
	//other.receiveMessage(EventMessage::Hit_Citizen, (void*)&hitdir);
}

void EventPolice::receiveMessage(EventMessage message, void * param)
{
}

void EventPolice::change_Animation(Animation animID, float animFrame, float animSpeed, bool isLoop, float blendRate) {
	animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);
}

void EventPolice::change_State(State state)
{
	state_ = state;


	switch (state_)
	{
	case EventPolice::State::Idle:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE_IDLE));
		change_Animation(AnimConverter.at(EventPolice::State::Idle).animation, 0.0f, 0.0f, false);//アニメーションさせない
		break;
	case EventPolice::State::Walk:
		change_Animation(AnimConverter.at(EventPolice::State::Walk).animation, 0.0f, 1.0f, AnimConverter.at(EventPolice::State::Idle).isLoop);//走るアニメーションさせる
																																			  //animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE_RUN));
		break;
	case EventPolice::State::Down:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE_IDLE));
		change_Animation(AnimConverter.at(EventPolice::State::Idle).animation, 0.0f, 0.0f, false);//アニメーションさせない
		break;
	default:
		break;
	}

}

void EventPolice::idle(float deltaTime) {
	//setPath();//ループさせるときはコメントアウトを解除
	//change_State(State::Walk);


	//dead();//自身を消す処理 ループさせる際はコメントアウト
	return;
	//dead();
	//return;
	//if (animation_.IsAnimEnd()) {
}



void EventPolice::walk(float deltaTime) {
	if (path_.empty()) {
		change_State(State::Idle);
		return;
	}
	//float power = 3.0f;
	Vector3 toTargetPosition = (path_.back() - position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
																				//OutputDebugString((std::to_string(checkIsLeftDot) + ":").c_str());


	Vector3 forwardVector = path_.back() - prevPath_;//経路の前方ベクトル
	Vector2	forwardVectorv2 = Vector2{ forwardVector.x,forwardVector.z };
	Vector3 leftVector = Matrix::CreateWorld(path_.back(), forwardVector, Vector3::Up).Left();//経路の横方向ベクトル
	Vector2 leftVectorv2 = Vector2{ leftVector.x,leftVector.z };
	Vector3 toCitizen = position_ - path_.back();//経路から自身に向かうベクトル
	Vector2 toCitizenv2 = Vector2{ toCitizen.x,toCitizen.z };

	if (Vector2::Angle(Vector2{ rotation_.Forward().x,rotation_.Forward().z }, forwardVectorv2) >= 90.0f) {//自身の向きが経路に対して横以上(逆向き)になったら
		toForward();//強制的に前を向く
	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*13.0f);//スムーズに曲がってもらうために*13.0fを追加
																				   //if (extrudedflag_ == false)
	position_ += rotation_.Forward()*1.0f;//テストのために0.3f→1.0fに変更
	//エネミーの少し手前で止まるようにする
	if (Vector2::Cross(leftVectorv2, toCitizenv2) >= -6.0f) {//ポイント上に横線を引き、そのラインを越えたら
		change_State(State::Idle);
	}
}

void EventPolice::down(float deltaTime)
{
	change_State(State::Walk);
}

void EventPolice::setPath()
{
	path_ = WalkPathReader::getInstance().getPoliceWalkList(0);//現状一つにまとめているので0を取得している
	position_ = path_[type_];//自分の位置を初期ポイントに設定する
	prevPath_ = position_;
	//目的地をエネミーの座標にする
	path_.push_back(world_->findActor("Enemy")->getPosition());
}

void EventPolice::toForward()
{
	Vector2 prev_currentpathv2;//前のポイントから現在のポイントへ向かうベクトル
	prev_currentpathv2.x = path_.back().x - prevPath_.x;
	prev_currentpathv2.y = path_.back().z - prevPath_.z;
	prev_currentpathv2.Normalize();
	rotation_.Forward(Vector3{ prev_currentpathv2.x,0.0f,prev_currentpathv2.y });//自身の回転行列の前方向を上で作ったベクトルに置き換え
	rotation_.NormalizeRotationMatrix();//正規化する
}
