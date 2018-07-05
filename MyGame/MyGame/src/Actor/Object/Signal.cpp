#include "Signal.h"
#include"../../Scene/Manager/GameDataManager.h"

Signal::Signal(IWorld * world){
	ci_signal_state_ = Citizensignal::Red;
	ca_signal_state_ = Carsignal::Green;
	ci_crosswalk_.load("res/Data/citizencrosswalk.csv");
	ci_change_signal_.load("res/Data/changesignal.csv");
	car_crosswalk_.load("res/Data/carcrosswalk.csv");
}


void Signal::update(float deltaTime)
{
	ci_sidewalk_flag_ = false;
	car_sidewalk_flag_ = false;
	deltaTime_ = deltaTime;
	//�Ԃ̏���
	car();
	//�s���̏���
	citizen();
	
	car_signal_yellow();//�ԐM�������̂Ƃ��ɉ������邩�̏���
	citizen_signal_yellow();//���s�ҐM�������̂Ƃ��ɉ������邩�̏���
	citizen_signal_green();//���s�ҐM�����̂Ƃ��ɉ������邩�̏���
	SignalSet();//�M���̏�Ԃ𑗂�
}

void Signal::draw() const
{
	//DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "%d", cichangesignal_.columns());
	//DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "�ԐM��%d,���M��%d", ca_signal_state_,ci_signal_state_);
	//DebugDraw::DebugDrawFormatString(200, 400, GetColor(255, 255, 255), "�s��%d,��%d", ci_sidewalk_flag_, car_sidewalk_flag_);
	
}
void Signal::car()
{
	//�Ԃ�ActorPtr���X�g���擾
	auto carlist = GameDataManager::getInstance().getCarList();
	//���X�g���̎Ԃ̏����擾
	for (auto& at : carlist)
	{
		Vector3 pos;
		pos = at.lock()->getPosition();
		for (int i = 0; i < car_crosswalk_.rows(); i++)
		{
			//�Ԃ����f�����͈̔͂ɓ�������
			if (pos.x > car_crosswalk_.geti(i, 0) && pos.x < car_crosswalk_.geti(i, 1) && pos.z > car_crosswalk_.geti(i, 2) && pos.z < car_crosswalk_.geti(i, 3))
			{
				car_sidewalk_flag_ = true;//�Ԃ����f�����̒��ɂ���t���O��true
				break;
			}
		}
	}
}
void Signal::citizen()
{
	//�s����ActorPtr���X�g���擾
	auto citizenlist = GameDataManager::getInstance().getCitizenList();
	//���X�g���̎s���̏����擾
	for (auto& at : citizenlist) {
		Vector3 pos;
		pos = at.lock()->getPosition();
		for (int i = 0; i < ci_crosswalk_.rows(); i++)
		{
			//�s�������f�����͈̔͂ɓ�������
			if (pos.x > ci_crosswalk_.geti(i, 0) && pos.x < ci_crosswalk_.geti(i, 1) && pos.z > ci_crosswalk_.geti(i, 2) && pos.z < ci_crosswalk_.geti(i, 3))
			{
				ci_sidewalk_flag_ = true;//�s�������f�����̒��ɂ���t���O��true
				break;
			}
		}
		for (int i = 0; i < ci_change_signal_.rows(); i++)
		{
			//�ԐM�����Ԃ��ݒ�͈͓��Ƀv���C���[�����邩�Ԃ����f�����ɓ����Ă��Ȃ���ΎԐM�������F�ɂ���
			if ((pos.x > ci_change_signal_.geti(i, 0) && pos.x < ci_change_signal_.geti(i, 1) && pos.z > ci_change_signal_.geti(i, 2) && pos.z < ci_change_signal_.geti(i, 3)) && ca_signal_state_ != Carsignal::Red &&car_sidewalk_flag_ == false)
			{
				ca_signal_state_ = Carsignal::Yellow;
				break;
			}
		}
	}
	//���݂����s�ҐM���������f�����ɕ��s�҂����Ȃ����M����10�b�o�߂�����
	if (ci_signal_state_ == Citizensignal::Green && ci_green_count_flag_ == true && ci_sidewalk_flag_ == false)
	{
		ci_signal_state_ = Citizensignal::Yellow;
		ci_green_count_ = 0;
		ci_green_count_flag_ = false;
	}
}
//�ԐM�������̂Ƃ��ɉ������邩�̏���
void Signal::car_signal_yellow()
{
	if (ca_signal_state_ == Carsignal::Yellow)
		ca_yellow_count_ += deltaTime_;
	else
		ca_yellow_count_ = 0;
	if (ca_yellow_count_ > yellow_time_)
	{
		ca_signal_state_ = Carsignal::Red;
		ci_signal_state_ = Citizensignal::Green;
	}
}
//���s�ҐM�������̂Ƃ��ɉ������邩�̏���
void Signal::citizen_signal_yellow()
{
	if (ci_signal_state_ == Citizensignal::Yellow)
		ci_yellow_count_ += deltaTime_;
	else
		ci_yellow_count_ = 0;
	if (ci_yellow_count_ > yellow_time_)
	{
		ci_signal_state_ = Citizensignal::Red;
		ca_signal_state_ = Carsignal::Green;
	}
}
//���s�ҐM�����̂Ƃ��ɉ������邩�̏���
void Signal::citizen_signal_green()
{
	if (ci_signal_state_ == Citizensignal::Green)
	{
		ci_green_count_ += deltaTime_;
	}
	else
		ci_green_count_ = 0;
	if (ci_green_count_ > 10)
	{
		ci_green_count_flag_ = true;
	}
}
//�M���̏�Ԃ𑗂�
void Signal::SignalSet()
{
	//bool��
	//�ԐM���̏�Ԃ�n��
	if (ca_signal_state_ == Carsignal::Yellow || ca_signal_state_ == Carsignal::Red)
	{
		GameDataManager::getInstance().setCarSignal(false);
	}
	else
	{
		GameDataManager::getInstance().setCarSignal(true);
	}
	//���s�ҐM���̏�Ԃ�n��
	if (ci_signal_state_ == Citizensignal::Yellow || ci_signal_state_ == Citizensignal::Red)
	{
		GameDataManager::getInstance().setCitizenSignal(false);
	}
	else
	{
		GameDataManager::getInstance().setCitizenSignal(true);
	}
	//enumclass��
	switch (ca_signal_state_)
	{
	case Carsignal::Red:
		GameDataManager::getInstance().setCarSignalNum(Signal_Red);
		break;
	case Carsignal::Yellow:
		GameDataManager::getInstance().setCarSignalNum(Signal_Yellow);
		break;
	case Carsignal::Green:
		GameDataManager::getInstance().setCarSignalNum(Signal_Green);
		break;
	}
	switch (ci_signal_state_)
	{
	case Citizensignal::Red:
		GameDataManager::getInstance().setCitizenSignalNum(Signal_Red);
		break;
	case Citizensignal::Yellow:
		GameDataManager::getInstance().setCitizenSignalNum(Signal_Yellow);
		break;
	case Citizensignal::Green:
		GameDataManager::getInstance().setCitizenSignalNum(Signal_Green);
		break;
	}
}

void Signal::onCollide(Actor & other)
{
}

void Signal::receiveMessage(EventMessage message, void * param)
{
}