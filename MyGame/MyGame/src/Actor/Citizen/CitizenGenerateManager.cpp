#include "CitizenGenerateManager.h"
#include"Citizen.h"
#include"../../Scene/Manager/GameDataManager.h"
#include <random>

static const std::vector<float> defaultTime{
	//30.0f,30.0f,30.0f,30.0f,30.0f,30.0f,//������citizen1�`6�̃X�|�[�����Ԃ̊Ǘ�
	1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,//������citizen1�`6�̃X�|�[�����Ԃ̊Ǘ�
	//5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,//������citizen1�`6�̃X�|�[�����Ԃ̊Ǘ�
	//10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,//������citizen1�`6�̃X�|�[�����Ԃ̊Ǘ�
	//13.0f,13.0f,13.0f,13.0f,13.0f,13.0f,//������citizen1�`6�̃X�|�[�����Ԃ̊Ǘ�
};
CitizenGenerateManager::CitizenGenerateManager() :
	world_(nullptr) {
	timer_.resize(defaultTime.size());
}

void CitizenGenerateManager::setWorld(IWorld * world)
{
	world_ = world;
}

void CitizenGenerateManager::initialize()
{
	for (int i = 0; i < timer_.size(); i++) {
		timer_[i] = defaultTime[i];
		for (int j = 0; j < OneRouteMax_; j++)
		GameDataManager::getInstance().setCiAlive(false, i);
	}
}

void CitizenGenerateManager::update(float deltaTime)
{
	for (int i = 0; i < timer_.size(); i++) {
		timer_[i] -= deltaTime;
		//���u����ނ������_���ɐ������鏈��
		MODEL_ID model_type;
		std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
		std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
		std::uniform_int_distribution<> rand(0, 1);        // [0, 1] �͈͂̈�l����
		switch (rand(mt))
		{
		case 0:
			model_type = MODEL_ID::MODEL_MOB_PHONE;
			break;
		case 1:
			model_type = MODEL_ID::MODEL_MOB_BAG;
			break;
		case 2:
			model_type = MODEL_ID::MODEL_MOB;
			break;
		}
		auto citizen = std::make_shared<Citizen>(world_, model_type, i);//�����p
		std::list<std::weak_ptr<Actor>> ci_list = GameDataManager::getInstance().getCitizenList();//�s���|�C���^���X�g���擾
		//Vector3 playerpos = world_->findActor("Player")->getPosition();
		for (auto& at : ci_list)
		{
			auto CitizenPtr = std::static_pointer_cast<Citizen>(at.lock());//�q�����w���|�C���^
			if (CitizenPtr->Get_Type() == i)
				Path_Size_Half_ = CitizenPtr->Get_Path_Size_Half();//�ړI�n�̔����܂Ői�񂾂��̃t���O���i�[����
				//cipos_ = at.lock()->getPosition();
		}
		//�^�C�������āA�������[�g�̐l����0�������́A�������݉\�l���ȏ�ł͂Ȃ������^�C�v�̎s�����ړI�n�̔����܂Ői��ł����琶������
		if (timer_[i] <= 0.0f &&GameDataManager::getInstance().getCiAlive(i)== 0 || (GameDataManager::getInstance().getCiAlive(i) != OneRouteMax_&& Path_Size_Half_ == true))//&&cipos_.Distance(cipos_, playerpos) < 200)
		{
			timer_[i] = defaultTime[i];

			
			world_->addActor(ActorGroup::CITIZEN_ACTOR, citizen);
			GameDataManager::getInstance().addCitizenList(citizen);
			GameDataManager::getInstance().addAvoidTarget(citizen);
		}
	}
}
