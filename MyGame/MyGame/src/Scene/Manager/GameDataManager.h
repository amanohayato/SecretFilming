#pragma once
#include<memory>
#include<list>
#include"../../Actor/ActorPtr.h"
#include"../../Math/Vector2.h"
//#include"../../World/IWorld.h"


class GameDataManager {
	GameDataManager() {}
public:
	static GameDataManager& getInstance() {
		static GameDataManager gdm;
		return gdm;
	}

	void initialize();
	void addAvoidTarget(ActorPtr ptr);//�s���p�ɃG�l�~�[�ƃv���C���[�̍��W���擾����ړI�Ŏg�p
	void addCitizenList(ActorPtr ptr);//�M���p�Ɏs����ActorPtr���擾����ړI�Ŏg�p
	void addCarList(ActorPtr ptr);//�M���p�ɎԂ�ActorPtr���擾����ړI�Ŏg�p
	void removeAvoidTarget(const ActorPtr& ptr);
	void removeCitizenList(const ActorPtr& ptr);
	void removeCarList(const ActorPtr& ptr);
	std::list<std::weak_ptr<Actor>> getAvoidTarget()const;
	std::list<std::weak_ptr<Actor>> getCitizenList()const;
	std::list<std::weak_ptr<Actor>> getCarList()const;

	// �G�l�~�[�̃S�[�����B�����ݒ�
	void setEnemyGoal(bool is_goal);
	// �G�l�~�[�̃S�[�����B������擾
	bool getEnemyGoal() const;

	// �N���A��������ݒ�
	void setScore(int score);
	// �N���A���������擾
	int getScore() const;
	//�s��1�`6�����l�����Ă��邩��ݒ�
	void setCiAlive(bool alive,int type);
	//�s��1�`6�����l�����Ă��邩���擾
	int getCiAlive(int type)const;
	//�Ԃ����䐶���Ă��邩��ݒ�
	void setCarAlive(bool alive, int type);
	//�Ԃ����䐶���Ă��邩���擾
	int getCarAlive(int type)const;
	//�ԐM������
	void setCarSignal(bool carsignal);
	bool getCarSignal()const;
	//���s�ҐM������
	void setCitizenSignal(bool cisignal);
	bool getCitizenSignal()const;
	//�G�l�~�[�̓������
	void setEnemyEscape(bool escape);
	bool getEnemyEscape()const;
	//�ԐM������
	void setCarSignalNum(int car_signal);
	int getCarSignalNum()const;
	//���s�ҐM������
	void setCitizenSignalNum(int car_signal);
	int getCitizenSignalNum()const;

	Vector2 getMapSize()const;
	void setMapSize(const Vector2& size);

	float getCameraSens()const;
	void setCameraSens(float value);

	bool getGameStop()const;
	void setGameStop(bool is_game_stop);

	int getEscapeCount();
	void addEscapeCount(int value = 1);

	int getPhotoCount();
	void addPhotoCount(int value = 1);


private:
	static const int oneroutemax_ = 10;//1���[�g�̍ő�l���Ƒ䐔
	static const int maxtype = 10;//�^�C�v�̍ő吔
	std::list<std::weak_ptr<Actor>> avoidTargets_;
	std::list<std::weak_ptr<Actor>> CitizenList_;
	std::list<std::weak_ptr<Actor>> CarList_;
	bool is_enemy_goal_{ false };
	int score_{ 0 };
	int cialive_[20]{};//�s��20�p�^�[��(��)�܂ł̔z��
	int caralive_[20]{};//��20�p�^�[��(��)�܂ł̔z��
	bool carsignal_ = {false};
	bool cisignal_ = { false };
	bool escape_ = {false};
	int car_signal_ = { 0 };
	int ci_signal_ = { 0 };
	Vector2 mapSize_{ Vector2::Zero };
	float cameraSens_{ 0.5f };
	bool is_game_stop_ = false;

	int escapeCount_{ 0 };
	int photoCount_{ 0 };
};