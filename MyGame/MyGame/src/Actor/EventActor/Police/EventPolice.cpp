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
	//�`��ʒu�����킹��(�Ō��Vector3�̓��f�����g�̃Y��)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//�O������킹��
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
	//�`��ʒu�����킹��(�Ō��Vector3�̓��f�����g�̃Y��)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//�O������킹��
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
		change_Animation(AnimConverter.at(EventPolice::State::Idle).animation, 0.0f, 0.0f, false);//�A�j���[�V���������Ȃ�
		break;
	case EventPolice::State::Walk:
		change_Animation(AnimConverter.at(EventPolice::State::Walk).animation, 0.0f, 1.0f, AnimConverter.at(EventPolice::State::Idle).isLoop);//����A�j���[�V����������
																																			  //animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE_RUN));
		break;
	case EventPolice::State::Down:
		animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE_IDLE));
		change_Animation(AnimConverter.at(EventPolice::State::Idle).animation, 0.0f, 0.0f, false);//�A�j���[�V���������Ȃ�
		break;
	default:
		break;
	}

}

void EventPolice::idle(float deltaTime) {
	//setPath();//���[�v������Ƃ��̓R�����g�A�E�g������
	//change_State(State::Walk);


	//dead();//���g���������� ���[�v������ۂ̓R�����g�A�E�g
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
	Vector3 toTargetPosition = (path_.back() - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
																				//OutputDebugString((std::to_string(checkIsLeftDot) + ":").c_str());


	Vector3 forwardVector = path_.back() - prevPath_;//�o�H�̑O���x�N�g��
	Vector2	forwardVectorv2 = Vector2{ forwardVector.x,forwardVector.z };
	Vector3 leftVector = Matrix::CreateWorld(path_.back(), forwardVector, Vector3::Up).Left();//�o�H�̉������x�N�g��
	Vector2 leftVectorv2 = Vector2{ leftVector.x,leftVector.z };
	Vector3 toCitizen = position_ - path_.back();//�o�H���玩�g�Ɍ������x�N�g��
	Vector2 toCitizenv2 = Vector2{ toCitizen.x,toCitizen.z };

	if (Vector2::Angle(Vector2{ rotation_.Forward().x,rotation_.Forward().z }, forwardVectorv2) >= 90.0f) {//���g�̌������o�H�ɑ΂��ĉ��ȏ�(�t����)�ɂȂ�����
		toForward();//�����I�ɑO������
	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*13.0f);//�X���[�Y�ɋȂ����Ă��炤���߂�*13.0f��ǉ�
																				   //if (extrudedflag_ == false)
	position_ += rotation_.Forward()*1.0f;//�e�X�g�̂��߂�0.3f��1.0f�ɕύX
	//�G�l�~�[�̏�����O�Ŏ~�܂�悤�ɂ���
	if (Vector2::Cross(leftVectorv2, toCitizenv2) >= -6.0f) {//�|�C���g��ɉ����������A���̃��C�����z������
		change_State(State::Idle);
	}
}

void EventPolice::down(float deltaTime)
{
	change_State(State::Walk);
}

void EventPolice::setPath()
{
	path_ = WalkPathReader::getInstance().getPoliceWalkList(0);//�����ɂ܂Ƃ߂Ă���̂�0���擾���Ă���
	position_ = path_[type_];//�����̈ʒu�������|�C���g�ɐݒ肷��
	prevPath_ = position_;
	//�ړI�n���G�l�~�[�̍��W�ɂ���
	path_.push_back(world_->findActor("Enemy")->getPosition());
}

void EventPolice::toForward()
{
	Vector2 prev_currentpathv2;//�O�̃|�C���g���猻�݂̃|�C���g�֌������x�N�g��
	prev_currentpathv2.x = path_.back().x - prevPath_.x;
	prev_currentpathv2.y = path_.back().z - prevPath_.z;
	prev_currentpathv2.Normalize();
	rotation_.Forward(Vector3{ prev_currentpathv2.x,0.0f,prev_currentpathv2.y });//���g�̉�]�s��̑O��������ō�����x�N�g���ɒu������
	rotation_.NormalizeRotationMatrix();//���K������
}
