#include "CarGenerateManager.h"
#include"Car.h"
#include"../../World/IWorld.h"
#include"../../Scene/Manager/GameDataManager.h"
#include <random>

static const std::vector<float> defaultTime{
	//16.0f,16.0f,16.0f,18.0f,//ここでcar1～4のスポーン時間の管理
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
	//初期化
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
		//タイムが0以下になって同じルートの車の数が同時存在可能数でなければ生成
		if (timer_[i] <= 0.0f && GameDataManager::getInstance().getCarAlive(i) != OneRouteMax_) {
			timer_[i] = defaultTime[i];
			//モデルの種類
			MODEL_ID model_type1;
			MODEL_ID model_type2;
			MODEL_ID model_type3;
			//スポーンさせる向きを判断
			bool is_front = false;
			//タイプによって判別する
			std::random_device rnd;     // 非決定的な乱数生成器を生成
			std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
			std::uniform_int_distribution<> rand(0, 3);        // [0, 1] 範囲の一様乱数
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
			GameDataManager::getInstance().addCarList(car);//生成した車のポインタを送る
		}
	}
}
