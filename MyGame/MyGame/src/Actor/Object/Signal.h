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

	//�ڐG��
	virtual void onCollide(Actor& other) override;

	virtual void receiveMessage(EventMessage message, void * param) override;
private:
	static const int yellow_time_ = 3;//�M�������F����Ԃɕς�鎞��(�b)
	static const int red_time_ = 10;//���s�ҐM�����΂��物�F�ɕς�鎞��(�b)


	MODEL_ID modelid_;
	Citizensignal ci_signal_state_;//���s�ҐM���̏��
	Carsignal ca_signal_state_;//�ԐM���̏��
	CsvReader ci_change_signal_;//���s�ҐM������������͈�
	CsvReader ci_crosswalk_;//�����Ŏs�����~�܂�͈�
	CsvReader car_crosswalk_;//�����ŎԂ��~�܂�͈�
	float ca_yellow_count_ = 0;//�Ԃ̉��F�M���J�E���g�p
	float ci_yellow_count_ = 0;//���s�҂̉��F�M���J�E���g�p
	float ci_green_count_ = 0;//���s�҂̐M���J�E���g�p
	bool ci_green_count_flag_ = false;//�M���̃J�E���g���I������t���O
	float deltaTime_;
	bool car_sidewalk_flag_ = false;//�Ԃ����f�������ɂ��邩�H
	bool ci_sidewalk_flag_ = false;//���s�҂����f�������ɂ��邩�H
};