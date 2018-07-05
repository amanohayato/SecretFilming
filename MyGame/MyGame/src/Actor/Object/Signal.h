#pragma once
#include"../Actor.h"
#include"../../ID/EnumIDs.h"
#include "../../Resource/CsvReader.h"

class Signal :public Actor {
	enum class Citizensignal
	{
		Red,
		Yellow,
		Green
	};
	enum class Carsignal
	{
		Red,
		Yellow,
		Green
	};
private:
public:
	Signal(IWorld* world);

	void update(float deltaTime);

	void draw()const;

	void car();

	void citizen();

	void car_signal_yellow();

	void citizen_signal_yellow();

	void citizen_signal_green();

	void SignalSet();

	//接触時
	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	static const int yellow_time_ = 3;//信号が黄色から赤に変わる時間(秒)
	static const int red_time_ = 10;//歩行者信号が緑から黄色に変わる時間(秒)


	MODEL_ID modelid_;
	Citizensignal ci_signal_state_;//歩行者信号の状態
	Carsignal ca_signal_state_;//車信号の状態
	CsvReader ci_change_signal_;//歩行者信号が反応する範囲
	CsvReader ci_crosswalk_;//歩道で市民が止まる範囲
	CsvReader car_crosswalk_;//歩道で車が止まる範囲
	float ca_yellow_count_ = 0;//車の黄色信号カウント用
	float ci_yellow_count_ = 0;//歩行者の黄色信号カウント用
	float ci_green_count_ = 0;//歩行者の青信号カウント用
	bool ci_green_count_flag_ = false;//青信号のカウントが終わったフラグ
	float deltaTime_;
	bool car_sidewalk_flag_ = false;//車が横断歩道内にいるか？
	bool ci_sidewalk_flag_ = false;//歩行者が横断歩道内にいるか？
};