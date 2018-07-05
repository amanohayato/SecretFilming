#include "Citizen.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Field/WalkGraph.h"
#include"WalkPathReader.h"
#include"../../Scene/Manager/GameDataManager.h"
#include "../../Graphic/AnimLoader.h"
#include "../Enemy/EnemyBase.h"
#include"../Player/Player.h"



static constexpr float FOV = 30.0f;
static constexpr float MAX_AVOID_SPACE = 33.0f;
Citizen::Citizen(IWorld * world, MODEL_ID id,int type, const IBodyPtr & body):
	Actor(world,"Citizen",Vector3::Zero,body), animation_(Model::GetInstance().GetHandle(id)),modelid_(id),state_(State::Idle), type_(type)
	
{
	roadway_.load("res/Data/roadway.csv");
	crosswalk_.load("res/Data/citizencrosswalk.csv");
}

void Citizen::initialize()
{
	change_State(State::Walk);
	setPath();
}

void Citizen::update(float deltaTime)
{
	//�v���C���[�̃|�W�V�������擾
	playerpos_ = world_->findActor("Player")->getPosition();
	//�O��̃t���[���̃|�W�V�������L������
	beforpos_ = position_;
	//���s�ҐM���̏�Ԃ̎擾
	signal_ = GameDataManager::getInstance().getCitizenSignal();
	//�A�j���[�V�����̍X�V
	animation_.update(MathHelper::Sign(deltaTime)*0.5f);
	switch (state_)
	{
	case Citizen::State::Idle:
		idle(deltaTime);
		break;
	case Citizen::State::Walk:
		walk(deltaTime);
		break;
	case Citizen::State::Down:
		down(deltaTime);
		break;
	case Citizen::State::Jump:
		jump(deltaTime);
		break;
	case Citizen::State::Dash:
		dash(deltaTime);
		break;
	case Citizen::State::Surprised:
		surprised(deltaTime);
		break;
	}
	//�ԓ��̏���
	roadway();

	switch (state_)
	{
	case Citizen::State::Jump:
		return;
		break;
	case Citizen::State::Dash:
		return;
		break;
	case Citizen::State::Surprised:
		return;
	case Citizen::State::Down:
		return;
		break;
	}

	// �G�̉F���l���擾
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//�_���������Ԃ��擾
	int score = std::static_pointer_cast<EnemyBase>(enemy)->getBaseScore();
	enemypos_ = enemy->getPosition();
	//�G�l�~�[�Ƃ̋�������薢���ŃG�l�~�[���X�R�A�l���\��Ԃł���΂т������ԂɈڍs����
	if (score != 0 && position_.Distance(position_, enemypos_) < enemy_destance_)//enemy_destance_ //test�p1500
	{
		//change_State(State::Dash);
		change_State(State::Surprised);
	}
	/*
	if (type_ != 2)return;
	DrawFormatString(500, 550, GetColor(255, 255, 255), "%f", position_.x);
	DrawFormatString(500, 570, GetColor(255, 255, 255), "%f", position_.z);
	*/
}

void Citizen::draw() const
{
	//�`��ʒu�����킹��(�Ō��Vector3�̓��f�����g�̃Y��)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//�O������킹��
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));//*Matrix::CreateScale(Vector3{ 1.0f, 1.0f, 1.0f })
	//�����蔻��̕`��
	//body_->transform(getPose())->draw();
	//�ړI�n�̃f�o�b�N�\��
	for (auto& i : path_) {
		DebugDraw::DebugDrawSphere3D(i, 3.f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	}
	//�_�b�V����Ԃ̃r�b�N���}�[�N�̕`��
	if (state_ == State::Dash)
	{
		auto currentstate = std::static_pointer_cast<Player>(world_->findActor("Player"))->getStateType();
		if (currentstate == Player_State_ID::MapApp || currentstate == Player_State_ID::SetUp)return;
		Vector3 drawPos = position_;
		drawPos.y = 19.0f;
		Vector2 origin = Vector2{ 0.5f, 0.0f };
		Model::GetInstance().Draw2D(MODEL_ID::SPRITE_EXCLAMATION, drawPos, 0, 10, origin, 0);
	}

	
	
}
void Citizen::shadowDraw() const
{
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//�O������킹��
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));//*Matrix::CreateScale(Vector3{ 1.0f, 1.0f, 1.0f })
}

void Citizen::end()
{
}

void Citizen::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Citizen, (void*)&hitdir);
}

void Citizen::receiveMessage(EventMessage message, void * param)
{
	
	if (message == EventMessage::Hit_Player || message == EventMessage::Hit_Enemy)
	{
		hit_Player(*(Vector3*)param);
	}
	//�I�u�W�F�N�g�ɓ��������Ƃ��̏���
	if (message == EventMessage::Hit_Object)
	{
		hit_Obj();
	}
}

void Citizen::change_Animation(Animation animID, float animFrame, float animSpeed, bool isLoop, float blendRate) {
	//animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);

	animation_.changeAnimation(AnimLoader::getInstance().getAnimKey(modelid_, (int)animID), isLoop, animSpeed, blendRate, animFrame);
}

void Citizen::change_State(State state)
{
	state_ = state;
	change_Animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).isLoop);

	switch (state_)
	{
	case Citizen::State::Idle:
		break;
	case Citizen::State::Walk:
		movepower_ = 0.5f;
		break;
	case Citizen::State::Down:
		break;
	case Citizen::State::Jump:
		break;
	case Citizen::State::Dash:
		movepower_ = 1.0f;
		break;
	case Citizen::State::Surprised:
		break;
	default:
		break;
	}
}

void Citizen::hit_Player(Vector3 & dir)
{
	dir.y = 0;
	//velocity_ += dir * 0.02f;//�Փ˗�
	velocity_ = dir * 0.1f;//�Փ˗�
	extrudedflag_ = true;//������т̃t���O��true�ɂ���
	change_State(State::Jump);
}

void Citizen::hit_Obj()
{
	//x��z�̂����A�߂��ق��̍��W��I�����č��킹��
	float x, z;
	x = std::abs(path_.front().x - position_.x);
	z = std::abs(path_.front().z - position_.z);
	//1��̂ݔ��� �ړI�n��V���ɐݒ肷��
	if (x < z && obj_hit_flag_ == false)
	{
		prevPath_ = position_;
		path_.push_front(Vector3(path_.front().x, 10, position_.z));
	}
	else if (obj_hit_flag_ == false)
	{
		prevPath_ = position_;
		path_.push_front(Vector3(position_.x, 10, path_.front().z));
	}
	//�I�u�W�F�N�g�ɓ���������q�b�g�t���O��true�ɂ���
	obj_hit_flag_ = true;
	//�n�}�肪�Ȃ����̃f�o�b�O�\��
	//DebugDraw::DebugDrawFormatString(500, 400, GetColor(255, 255, 255), "%f,%f", position_.x, position_.z);
}

bool Citizen::Get_Path_Size_Half()
{
	float a;
	if (path_.size() != 0)//0������Ȃ�����
		a = (float)first_path_size_ / (float)path_.size();
	else
		return true;//0��������true
	if (a >= 2)//Path�T�C�Y�������T�C�Y�̔����ȉ��Ȃ�true��Ԃ�
		return true;
	else//�S�Ăɓ��Ă͂܂�Ȃ����false��Ԃ�
		return false;
}

int Citizen::Get_Type()
{
	return type_;
}

void Citizen::idle(float deltaTime){
	

	//playerpos_ = world_->findActor("Player")->getPosition();
	change_State(State::Walk);
	if (position_.Distance(position_, playerpos_) < player_distance_)//�v���C���[�Ƃ̋�����200�����Ȃ烋�[�v����
	{
		setLoop();
		return;
	}
	//�s���̐����t���O��false�ɂ��đ���
	GameDataManager::getInstance().setCiAlive(false, type_);
	GameDataManager::getInstance().removeCitizenList(this->shared_from_this());//�����Ă���s���̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
	GameDataManager::getInstance().removeAvoidTarget(this->shared_from_this());//�^�[�Q�b�g���玩�g���폜
	dead();//���g���������� ���[�v������ۂ̓R�����g�A�E�g
	return;
	//else
	//setPath();//���[�v������Ƃ��̓R�����g�A�E�g������
	//dead();
	//return;
	//if (animation_.IsAnimEnd()) {
}
void Citizen::walk(float deltaTime){

	
	if (path_.empty()) {
		change_State(State::Idle);
		return;
	}
	
	//float power = 3.0f;
	Vector3 toTargetPosition = (path_.front()- position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	//OutputDebugString((std::to_string(checkIsLeftDot) + ":").c_str());


	avoid(deltaTime);


	Vector3 forwardVector = path_.front() - prevPath_;//�o�H�̑O���x�N�g��
	Vector2	forwardVectorv2 = Vector2{ forwardVector.x,forwardVector.z };
	Vector3 leftVector = Matrix::CreateWorld(path_.front(), forwardVector, Vector3::Up).Left();//�o�H�̉������x�N�g��
	Vector2 leftVectorv2 = Vector2{ leftVector.x,leftVector.z };
	Vector3 toCitizen = position_ - path_.front();//�o�H���玩�g�Ɍ������x�N�g��
	Vector2 toCitizenv2 = Vector2{ toCitizen.x,toCitizen.z };

	if (Vector2::Angle(Vector2{ rotation_.Forward().x,rotation_.Forward().z }, forwardVectorv2) >= 90.0f) {//���g�̌������o�H�ɑ΂��ĉ��ȏ�(�t����)�ɂȂ�����
		toForward();//�����I�ɑO������
	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*30.0f);//�X���[�Y�ɋȂ����Ă��炤���߂�*13.0f��ǉ�
	//if (extrudedflag_ == false)
	position_ += rotation_.Forward()*movepower_;//�e�X�g�̂��߂�0.3f��1.0f�ɕύX

	if (Vector2::Cross(leftVectorv2, toCitizenv2) >= 0.0f){//�|�C���g��ɉ����������A���̃��C�����z������


	//if (Vector3::Distance(position_, path_.front()) <= 1.f) {

		//���̃|�C���g��ݒ�
		prevPath_ = path_.front();
		path_.pop_front();
		obj_hit_flag_ = false;
	}
	/*
	if (dash_count_ != 0 && state_ != State::Dash)
		change_State(State::Dash);
		*/
}

void Citizen::down(float deltaTime)
{
	if (position_.y > 10.0f)
		position_ -= velocity_;//�Փ˗p�̗�
	else if(signal_ == true)
	{
		//�W�����v���Ƀ_�E����ԂɈڍs�����Ƃ��̑΍�
		extrudedflag_ = false;
		count = 0;//�J�E���g��0�ɂ���
		position_.y = 10.0f;
		change_State(State::Walk);
	}
	
}

void Citizen::jump(float deltaTime)
{
	//������
	count += deltaTime;
	if (count >= 0.5f || extrudedflag_ == false)
	{
		extrudedflag_ = false;
		change_State(State::Walk);
		count = 0;
	}
	if (extrudedflag_ == true)
	{
		position_ += velocity_;//�Փ˗p�̗�
		count += deltaTime;//���Ԃ̃J�E���g
	}
	//�W�����v
	/*
	if (count >= 1.0f)
	{
		extrudedflag_ = false;
		count = 0;//�J�E���g��0�ɂ���
		change_State(State::Walk);
	}
	else if (count >= 0.5f)
	{
		position_ -= velocity_;//�Փ˗p�̗�
		count += deltaTime;//���Ԃ̃J�E���g
	}
	else if (extrudedflag_ == true)
	{
		position_ += velocity_ + rotation_.Backward();//�Փ˗p�̗� ���ɂ���΂�����
		count += deltaTime;//���Ԃ̃J�E���g
	}
	else if (extrudedflag_ == false && count <= 0)
	{
		extrudedflag_ = false;
		count = 0;//�J�E���g��0�ɂ���
		change_State(State::Walk);
		position_.y = 10.0f;
	}
	else if (extrudedflag_ == false)
	{
		position_ -= velocity_;//�Փ˗p�̗�
		count -= deltaTime;//���Ԃ̃J�E���g
	}*/
}

void Citizen::dash(float deltaTime)
{
	dash_count_ += deltaTime;
	//�_�b�V���̏���
	walk(deltaTime);
	if (dash_count_ >= 5.0f)
	{
		dash_count_ = 0;
		change_State(State::Walk);
	}
}

void Citizen::surprised(float deltaTime)
{
	//Vector3 target = (position_-enemypos_).Normalize();
	
	Vector3 dir = enemypos_ - position_;//�G�l�~�[�̕���
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);//�G�l�~�[�̕���������
	if(animation_.isEnd() == true)change_State(State::Dash);//�����ԂɈȍ~����
}

void Citizen::roadway()
{
	//�Z��������
	for (int j = 0; j < roadway_.rows(); j++) {
		for (int i = 0; i < crosswalk_.rows(); i++)
		{
			//���f�����͈̔͂ɓ����ĐM�����Ԃ�����������~�܂�
			if (position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3) && signal_ == false)
			{
				change_State(State::Down);
				breakflag = true;
				break;
			}
			//���f�����͈̔͂ɓ����ĐM�����ł���ΐi��
			else if (position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3))
			{
				breakflag = true;
				break;
			}
		}
		//��d���[�v���甲���鏈��
		if (breakflag)
			break;
		//�ԓ��ɐN�����Ȃ����� �v���C���[�ɂ����l�̏������L�q
		if (position_.x > roadway_.geti(j, 0) && position_.x < roadway_.geti(j, 1) && position_.z > roadway_.geti(j, 2) && position_.z <roadway_.geti(j, 3))
		{
			//�ԓ���`�̍��W�ɐN�������ہAposition�Ɣ�r���čŌ�ɏ����𖞂������̂�x��z���𔻒�
			int x0, x1, z2, z3;
			x0 = (int)floorf(std::abs(roadway_.geti(j, 0) - position_.x));
			x1 = (int)floorf(std::abs(roadway_.geti(j, 1) - position_.x));
			z2 = (int)floorf(std::abs(roadway_.geti(j, 2) - position_.z));
			z3 = (int)floorf(std::abs(roadway_.geti(j, 3) - position_.z));
			std::list<int> minimum = { x0,x1,z2,z3 };
			minimum.sort();
			//���f�����̂�x�Ȃ�z���W�͈ړ��\�ɁAz�Ȃ�x���W���ړ��\�ɂ���
			if (minimum.front() == x0 || minimum.front() == x1)
				position_.x = beforpos_.x;
			else if (minimum.front() == z2 || minimum.front() == z3)
				position_.z = beforpos_.z;
			extrudedflag_ = false;

			//�p�̃o�O�C����
			auto itr = minimum.begin();
			++itr;

			int corner;
			corner = *itr - minimum.front();
			
			if (corner <= 2)
			{
				position_ = beforpos_;
				//position_ += rotation_.Backward()*10;
				//break;
			}
			hit_Obj();
		}
	}
	breakflag = false;
	
}
//�����鏈��
void Citizen::avoid(float deltaTime)
{
	//�^�[�Q�b�g���W���擾����
	auto avoidTarget = GameDataManager::getInstance().getAvoidTarget();

	Vector2 posv2, pos_forwardv2, forwardv2,leftv2;
	forwardv2.x = rotation_.Forward().x;//���g�̑O�����x�N�g��
	forwardv2.y = rotation_.Forward().z;
	forwardv2 = forwardv2.Normalize();
	posv2.x = position_.x;//���g�̍��W
	posv2.y = position_.z;
	pos_forwardv2.x = posv2.x + forwardv2.x;//���g�̑O�������W
	pos_forwardv2.y = posv2.y + forwardv2.y;
	leftv2.x = rotation_.Left().x;//���g�̉������x�N�g��
	leftv2.y = rotation_.Left().z;



	//������s����

	Vector2 prevpathv2,prev_currentpathv2;//�o�H�x�N�g��
	prevpathv2.x = prevPath_.x;//�O��̃|�C���g
	prevpathv2.y = prevPath_.z;
	prev_currentpathv2.x = path_.front().x - prevPath_.x;//�O��̃|�C���g���猻�݂̃|�C���g�֌������x�N�g��
	prev_currentpathv2.y = path_.front().z - prevPath_.z;
	prev_currentpathv2.Normalize();

	float avoidDist = Vector2::Point_Distance(prev_currentpathv2, prevpathv2, posv2);//���݂̉��

	if (avoidDist >= MAX_AVOID_SPACE) {//��𕝂����e�͈͂𒴂�����
		toForward();//�����I�ɑO������
		return;
	}
	//������s�����I��


	////�����Ŕ��肷��
	//float slope = (pos_forwardv2.y - posv2.y) / (pos_forwardv2.x / posv2.x);//a
	//float coefficient = pos_forwardv2.y - (slope*pos_forwardv2.x);//b
	//
	//float slope_tangent = -(1 / slope);//a'


	constexpr float maxangle = 8.0f;//1�񓖂���̍ő��]��
	constexpr float avoidlength = 16.5f;//���
	constexpr float targetDistance = 16.5f*1.0f;//���͈�
	float angle = 0.0f;//��]��
	for (auto& at : avoidTarget) {
		Vector2 targetv2;//���Ώۂ̍��W
		targetv2.x = at.lock()->getPosition().x;
		targetv2.y = at.lock()->getPosition().z;

		if (Vector2::Distance(posv2, targetv2) >= targetDistance)continue;//���Ώۂ����苗���ȏ㗣��Ă����疳��
		if (at.lock()->getNumber() == getNumber())continue;//���g�Ɠ������ʔԍ��Ȃ疳��

		Vector2 AP;//���g������Ώۂ֌������x�N�g��
		AP.x = targetv2.x - posv2.x;
		AP.y = targetv2.y - posv2.y;

		if (Vector2::Cross(leftv2, AP) < 0.0f)continue;//��둤�������疳��

		float D = MathHelper::Abs(Vector2::Cross(forwardv2, AP));//forwardv2��AP�������镽�s�l�ӌ`�̖ʐς����߂�

		float L = Vector2::Distance(posv2, pos_forwardv2);//forwardv2�̒��������߂�

		float H = D / L;//��2���g����forwardv2,targetv2�̌�_����targetv2�܂ł̋��������߂�

		if (H > avoidlength)continue;//��𕝂𒴂��Ă����疳��

		angle += (avoidlength-H) * MathHelper::Sign(Vector2::Cross(forwardv2, AP));//��]�ʂ����Z

		//float coefficient_tangent = targetv2.y - slope_tangent * targetv2.x;//b'
		//
		//Vector2 intersect_point;
		//intersect_point.x = (coefficient_tangent - coefficient) / (slope - slope_tangent);
		//intersect_point.y = slope_tangent * intersect_point.x + coefficient_tangent;
		//
		//float distance = Vector2::Distance(targetv2, intersect_point);

		//DrawLine3D(VGet(targetv2.x,15.0f, targetv2.y), VGet(intersect_point.x,15.0f, intersect_point.y), GetColor(255, 0, 0));
		
		//Vector2 targetv2;
		//targetv2.x = at.lock()->getPosition().x - position_.x;
		//targetv2.y = at.lock()->getPosition().z - position_.z;
		//targetv2 = targetv2.Normalize();
		//
		//auto angle = Vector2::Angle(targetv2, forwardv2);
		//if (MathHelper::Abs(angle) <= FOV) {//���E���ɓ����Ă�����
		//
		//	float checkIsLeftCrossVector = Vector2::Cross(forwardv2, targetv2);//�O�ςō��E����
		//	OutputDebugString((std::to_string(checkIsLeftCrossVector)+ "\n").c_str());
		//	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftCrossVector*2.0f);
		//
		//}
		//else {
		//	OutputDebugString("\n");
		//
		//}
	}
	
	angle = MathHelper::Clamp(angle, -maxangle, maxangle);//��]�ʂ��ő��]�ʂ܂łɊۂ߂�
	
	
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), angle);//��]���s��
}
//�������� �ړI�n������
void Citizen::setPath()
{
	path_ = WalkPathReader::getInstance().getWalkList(type_);
	GameDataManager::getInstance().setCiAlive(true,type_);
	position_ = path_.front();//�����̈ʒu�������|�C���g�ɐݒ肷��
	prevPath_ = position_;
	first_path_size_ = (int)path_.size();
	path_.pop_front();//���̃|�C���g�֌�����
}
//�ړ������[�v�����鏈��
void Citizen::setLoop()
{
	path_ = WalkPathReader::getInstance().getWalkList(type_);
	position_ = path_.front();//�����̈ʒu�������|�C���g�ɐݒ肷��
	prevPath_ = position_;
	first_path_size_ = (int)path_.size();
	path_.pop_front();//���̃|�C���g�֌�����
}

void Citizen::toForward()
{ 
	Vector2 prev_currentpathv2;//�O�̃|�C���g���猻�݂̃|�C���g�֌������x�N�g��
	prev_currentpathv2.x = path_.front().x - prevPath_.x;
	prev_currentpathv2.y = path_.front().z - prevPath_.z;
	prev_currentpathv2.Normalize();
	rotation_.Forward(Vector3{ prev_currentpathv2.x,0.0f,prev_currentpathv2.y });//���g�̉�]�s��̑O��������ō�����x�N�g���ɒu������
	rotation_.NormalizeRotationMatrix();//���K������
}
