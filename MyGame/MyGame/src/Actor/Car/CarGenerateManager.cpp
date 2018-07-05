#include "CarGenerateManager.h"
#include"Car.h"
#include"../../World/IWorld.h"
#include"../../Scene/Manager/GameDataManager.h"
#include <random>

static const std::vector<float> defaultTime{
	//16.0f,16.0f,16.0f,18.0f,//������car1�`4�̃X�|�[�����Ԃ̊Ǘ�
	//5.0f,5.0f,5.0f,8.0f,
	1.0f,1.0f,1.0f,
};
CarGenerateManager::CarGenerateManager():
	world_(nullptr){
	timer_.resize(defaultTime.size());
}

void CarGenerateManager::setWorld(IWorld * world)
{
	world_ = world;
}

void CarGenerateManager::initialize()
{
	//������
	for (int i = 0; i < timer_.size(); i++) {
		timer_[i] = defaultTime[i];
		for (int j = 0; j < OneRouteMax_; j++)
			GameDataManager::getInstance().setCarAlive(false, i);
	}
}

void CarGenerateManager::update(float deltaTime)
{
	
	for (int i = 0; i < timer_.size(); i++) {
		timer_[i] -= deltaTime;
		//�^�C����0�ȉ��ɂȂ��ē������[�g�̎Ԃ̐����������݉\���łȂ���ΐ���
		if (timer_[i] <= 0.0f && GameDataManager::getInstance().getCarAlive(i) != OneRouteMax_) {
			timer_[i] = defaultTime[i];
			//���f���̎��
			MODEL_ID model_type1;
			MODEL_ID model_type2;
			MODEL_ID model_type3;
			//�X�|�[������������𔻒f
			bool is_front = false;
			//�^�C�v�ɂ���Ĕ��ʂ���
			std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
			std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
			std::uniform_int_distribution<> rand(0, 3);        // [0, 1] �͈͂̈�l����
			switch (rand(mt))
			{
			case 0:
				model_type1 = MODEL_ID::MODEL_CAR_BLUE1;
				model_type2 = MODEL_ID::MODEL_CAR_BLUE2;
				model_type3 = MODEL_ID::MODEL_CAR_BLUE_LAMP;
				break;
			case 1:
				model_type1 = MODEL_ID::MODEL_CAR_WHITE1;
				model_type2 = MODEL_ID::MODEL_CAR_WHITE2;
				model_type3 = MODEL_ID::MODEL_CAR_WHITE_LAMP;
				break;
			case 2:
				model_type1 = MODEL_ID::MODEL_CAR_GRAY1;
				model_type2 = MODEL_ID::MODEL_CAR_GRAY2;
				model_type3 = MODEL_ID::MODEL_CAR_GRAY_LAMP;
				break;
			case 3:
				model_type1 = MODEL_ID::MODEL_CAR_RED1;
				model_type2 = MODEL_ID::MODEL_CAR_RED2;
				model_type3 = MODEL_ID::MODEL_CAR_RED_LAMP;
				break;
			}
			switch (i)
			{
			case 1:
				is_front = true;
				break;
			case 5:
				is_front = true;
				break;
			}
			auto car = std::make_shared<Car>(world_,"Car", model_type1, model_type2, model_type3, i,is_front);
			world_->addActor(ActorGroup::CAR_ACTOR, car);
			GameDataManager::getInstance().addCarList(car);//���������Ԃ̃|�C���^�𑗂�
		}
	}
}
