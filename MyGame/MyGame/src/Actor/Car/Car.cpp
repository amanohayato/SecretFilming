#include "Car.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"
#include"../Citizen/WalkPathReader.h"
#include"../../Scene/Manager/GameDataManager.h"
#include"../../Sound/Sound.h"

Car::Car(IWorld * world,std::string name, MODEL_ID id1, MODEL_ID id2, MODEL_ID id3, int type, bool is_front, const IBodyPtr & body):
	Actor(world,name,Vector3::Zero,body), modelid_(id1), modelid_move1_(id1), modelid_move2_(id2), modelid_lamp_(id3),is_front_(is_front){
	crosswalk_.load("res/Data/carcrosswalk.csv");
	path_ = WalkPathReader::getInstance().getDriveList(type);//carmap�̓ǂݍ���(Vector��carmap1 2 3 4��eventcar1 2 3 �������Ă���)
	position_ = path_.front();
	type_ = type;//�ǂ̃��[�g�̎Ԃ����f����
	carstate_ = CarState::Move;
	GameDataManager::getInstance().setCarAlive(true, type);//���g���������ꂽ�琶���t���O��true�ɂ��đ���

}


void Car::update(float deltaTime)
{
	delta_time_ = deltaTime;
	
	//�ԐM���̏�Ԃ��擾����
	signal_ = GameDataManager::getInstance().getCarSignal();
	//���ȏ��y���W�𒴂��邩�ړI�n���Ȃ��Ȃ�Ǝ��g������
	if (path_.empty()|| position_.y >deadpos_y_) {
		GameDataManager::getInstance().setCarAlive(false, type_);//�����t���O��false�ɂ��đ���
		GameDataManager::getInstance().removeCarList(this->shared_from_this());//�����Ă���Ԃ̃|�C���^���i�[���Ă郊�X�g���玩�g���폜
		dead();
		return;
	}
	Signal();
}

void Car::draw() const
{
	//�X�|�[�����̎Ԃ̌���
	if (is_front_ == false)
	{
		Model::GetInstance().Draw(modelid_, Matrix(rotation_ * Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f) * Matrix::CreateScale((Vector3(1.2f, 1.2f, 1.2f)))).Translation(position_ + Vector3::Down*body_->radius()));//180�x��]�����ăX�P�[����1.2�{����
		
	}
	//�X�|�[�����̎Ԃ̌���(�t)
	else
	{
		Model::GetInstance().Draw(modelid_, Matrix(rotation_).Translation(position_ + Vector3::Down*body_->radius()));
	}
	//�����蔻��f�o�b�N�\��
	body_->transform(getPose())->draw();
}
void Car::shadowDraw() const
{
	draw();
}
//�Փ˂����烁�b�Z�[�W�𑗂�
void Car::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Car, (void*)&hitdir);
}
//���b�Z�[�W���󂯎��
void Car::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::Hit_Enemy)
	{
		hit_Enemy(*(Vector3*)param);
	}
}
void Car::change_State(CarState state)
{
	carstate_ = state;
	switch (carstate_)
	{
	case Car::CarState::Idle:
		Idle();
		break;
	case Car::CarState::Move:
		move();
		break;
	}
}
//�G�l�~�[�Ɠ��������Ƃ��̔���
void Car::hit_Enemy(const Vector3& dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	velocity_ = rotation_.Up() * 10 + dir_ * 3;
	velocity_ = Vector3::Normalize(velocity_);
	//��ɒ��ԃt���O��true�ɂ���
	enemyhitflag_ = true;

	Sound::GetInstance().Play3DSE(SE_ID::JUNCTION_HUTTOBI_VC_SE,(VECTOR*)&position_);
}

void Car::move()
{
	//�G���[�΍�
	if (path_.size() == 0)
		return;
	count_ += delta_time_;
	Vector3 toNextPoint = (path_.front() - position_).Normalize();//���g���玟�̒n�_�ւ̃x�N�g��
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toNextPoint);//�O�ςō��E����
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//��+���ςŎ��g�̉�]���l���������E����(���Ȃ獶�A���Ȃ�E)
	if (enemyhitflag_)
	{
		position_ += velocity_ * 2;
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Right(),1);
	}
	//�����̌����ɂ���Đ��ʑ�����둤���ǂ���ɐi�ނ�������
	else if (is_front_ == false)
	{
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*6.0f);
		position_ += rotation_.Forward()*3.0f;
	}
	else
	{
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Backward(), checkIsLeftDot*6.0f);
		position_ += rotation_.Backward()*3.0f;
	}
	//�ړI�n�ɂ����玟�̖ړI�n��
	if (Vector2::Distance(Vector2(position_.x, position_.z), Vector2(path_.front().x, path_.front().z)) <= 10.0f) {
		path_.pop_front();
	}
	if (count_ <= 0.05f)
		modelid_ = modelid_move1_;
	else if (count_ <= 0.1f)
		modelid_ = modelid_move2_;
	else
		count_ = 0;
}

void Car::Idle()
{
	//�Ԃ��~�܂�܂�
	modelid_ = modelid_lamp_;
}
//�M���̂Ƃ��̏���
void Car::Signal()
{
	for (int i = 0; i < crosswalk_.rows(); i++)
	{
		
		//�C�x���g�J�[�ł���ΐM���𖳎�����
		if (type_ == 4 || type_ == 5 || type_ == 6)
		{
			change_State(CarState::Move);
			break;
		}
		//�M�����ԂŎԂ��~�܂�͈͂ɓ�������Ԃ��~��Ԃɂ���
		if (signal_ == false && position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3))
		{
			change_State(CarState::Idle);
			break;
		}
		//����ȊO�̏����Ȃ瑖��
		else
		{
			change_State(CarState::Move);
		}
	}
}

void Car::setsignal(bool signal)
{
	signal_ = signal;
}
