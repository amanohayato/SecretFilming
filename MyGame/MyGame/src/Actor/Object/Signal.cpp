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
	//車の処理
	car();
	//市民の処理
	citizen();
	
	car_signal_yellow();//車信号が黄のときに何をするかの処理
	citizen_signal_yellow();//歩行者信号が黄のときに何をするかの処理
	citizen_signal_green();//歩行者信号が青のときに何をするかの処理
	SignalSet();//信号の状態を送る
}

void Signal::draw() const
{
	//DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "%d", cichangesignal_.columns());
	//DebugDraw::DebugDrawFormatString(200, 200, GetColor(255, 255, 255), "車信号%d,歩信号%d", ca_signal_state_,ci_signal_state_);
	//DebugDraw::DebugDrawFormatString(200, 400, GetColor(255, 255, 255), "市民%d,車%d", ci_sidewalk_flag_, car_sidewalk_flag_);
	
}
void Signal::car()
{
	//車のActorPtrリストを取得
	auto carlist = GameDataManager::getInstance().getCarList();
	//リスト内の車の情報を取得
	for (auto& at : carlist)
	{
		Vector3 pos;
		pos = at.lock()->getPosition();
		for (int i = 0; i < car_crosswalk_.rows(); i++)
		{
			//車が横断歩道の範囲に入ったら
			if (pos.x > car_crosswalk_.geti(i, 0) && pos.x < car_crosswalk_.geti(i, 1) && pos.z > car_crosswalk_.geti(i, 2) && pos.z < car_crosswalk_.geti(i, 3))
			{
				car_sidewalk_flag_ = true;//車が横断歩道の中にいるフラグをtrue
				break;
			}
		}
	}
}
void Signal::citizen()
{
	//市民のActorPtrリストを取得
	auto citizenlist = GameDataManager::getInstance().getCitizenList();
	//リスト内の市民の情報を取得
	for (auto& at : citizenlist) {
		Vector3 pos;
		pos = at.lock()->getPosition();
		for (int i = 0; i < ci_crosswalk_.rows(); i++)
		{
			//市民が横断歩道の範囲に入ったら
			if (pos.x > ci_crosswalk_.geti(i, 0) && pos.x < ci_crosswalk_.geti(i, 1) && pos.z > ci_crosswalk_.geti(i, 2) && pos.z < ci_crosswalk_.geti(i, 3))
			{
				ci_sidewalk_flag_ = true;//市民が横断歩道の中にいるフラグをtrue
				break;
			}
		}
		for (int i = 0; i < ci_change_signal_.rows(); i++)
		{
			//車信号が赤かつ設定範囲内にプレイヤーがいるかつ車が横断歩道に入っていなければ車信号を黄色にする
			if ((pos.x > ci_change_signal_.geti(i, 0) && pos.x < ci_change_signal_.geti(i, 1) && pos.z > ci_change_signal_.geti(i, 2) && pos.z < ci_change_signal_.geti(i, 3)) && ca_signal_state_ != Carsignal::Red &&car_sidewalk_flag_ == false)
			{
				ca_signal_state_ = Carsignal::Yellow;
				break;
			}
		}
	}
	//現在が歩行者信号が青かつ横断歩道に歩行者がいないかつ青信号で10秒経過したら
	if (ci_signal_state_ == Citizensignal::Green && ci_green_count_flag_ == true && ci_sidewalk_flag_ == false)
	{
		ci_signal_state_ = Citizensignal::Yellow;
		ci_green_count_ = 0;
		ci_green_count_flag_ = false;
	}
}
//車信号が黄のときに何をするかの処理
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
//歩行者信号が黄のときに何をするかの処理
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
//歩行者信号が青のときに何をするかの処理
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
//信号の状態を送る
void Signal::SignalSet()
{
	//boolで
	//車信号の状態を渡す
	if (ca_signal_state_ == Carsignal::Yellow || ca_signal_state_ == Carsignal::Red)
	{
		GameDataManager::getInstance().setCarSignal(false);
	}
	else
	{
		GameDataManager::getInstance().setCarSignal(true);
	}
	//歩行者信号の状態を渡す
	if (ci_signal_state_ == Citizensignal::Yellow || ci_signal_state_ == Citizensignal::Red)
	{
		GameDataManager::getInstance().setCitizenSignal(false);
	}
	else
	{
		GameDataManager::getInstance().setCitizenSignal(true);
	}
	//enumclassで
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