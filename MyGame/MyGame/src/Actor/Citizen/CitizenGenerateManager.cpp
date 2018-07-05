#include "CitizenGenerateManager.h"
#include"Citizen.h"
#include"../../Scene/Manager/GameDataManager.h"
#include <random>

static const std::vector<float> defaultTime{
	//30.0f,30.0f,30.0f,30.0f,30.0f,30.0f,//ここでcitizen1～6のスポーン時間の管理
	1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,//ここでcitizen1～6のスポーン時間の管理
	//5.0f,5.0f,5.0f,5.0f,5.0f,5.0f,//ここでcitizen1～6のスポーン時間の管理
	//10.0f,10.0f,10.0f,10.0f,10.0f,10.0f,//ここでcitizen1～6のスポーン時間の管理
	//13.0f,13.0f,13.0f,13.0f,13.0f,13.0f,//ここでcitizen1～6のスポーン時間の管理
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
		//モブを種類をランダムに生成する処理
		MODEL_ID model_type;
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand(0, 1);        // [0, 1] 範囲の一様乱数
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
		auto citizen = std::make_shared<Citizen>(world_, model_type, i);//生成用
		std::list<std::weak_ptr<Actor>> ci_list = GameDataManager::getInstance().getCitizenList();//市民ポインタリストを取得
		//Vector3 playerpos = world_->findActor("Player")->getPosition();
		for (auto& at : ci_list)
		{
			auto CitizenPtr = std::static_pointer_cast<Citizen>(at.lock());//子供を指すポインタ
			if (CitizenPtr->Get_Type() == i)
				Path_Size_Half_ = CitizenPtr->Get_Path_Size_Half();//目的地の半分まで進んだかのフラグを格納する
				//cipos_ = at.lock()->getPosition();
		}
		//タイムが来て、同じルートの人数が0もしくは、同時存在可能人数以上ではなく同じタイプの市民が目的地の半分まで進んでいたら生成する
		if (timer_[i] <= 0.0f &&GameDataManager::getInstance().getCiAlive(i)== 0 || (GameDataManager::getInstance().getCiAlive(i) != OneRouteMax_&& Path_Size_Half_ == true))//&&cipos_.Distance(cipos_, playerpos) < 200)
		{
			timer_[i] = defaultTime[i];

			
			world_->addActor(ActorGroup::CITIZEN_ACTOR, citizen);
			GameDataManager::getInstance().addCitizenList(citizen);
			GameDataManager::getInstance().addAvoidTarget(citizen);
		}
	}
}
