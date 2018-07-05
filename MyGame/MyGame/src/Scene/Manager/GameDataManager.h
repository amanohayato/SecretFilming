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
	void addAvoidTarget(ActorPtr ptr);//市民用にエネミーとプレイヤーの座標を取得する目的で使用
	void addCitizenList(ActorPtr ptr);//信号用に市民のActorPtrを取得する目的で使用
	void addCarList(ActorPtr ptr);//信号用に車のActorPtrを取得する目的で使用
	void removeAvoidTarget(const ActorPtr& ptr);
	void removeCitizenList(const ActorPtr& ptr);
	void removeCarList(const ActorPtr& ptr);
	std::list<std::weak_ptr<Actor>> getAvoidTarget()const;
	std::list<std::weak_ptr<Actor>> getCitizenList()const;
	std::list<std::weak_ptr<Actor>> getCarList()const;

	// エネミーのゴール到達判定を設定
	void setEnemyGoal(bool is_goal);
	// エネミーのゴール到達判定を取得
	bool getEnemyGoal() const;

	// クリアしたかを設定
	void setScore(int score);
	// クリアしたかを取得
	int getScore() const;
	//市民1～6が何人生きているかを設定
	void setCiAlive(bool alive,int type);
	//市民1～6が何人生きているかを取得
	int getCiAlive(int type)const;
	//車が何台生きているかを設定
	void setCarAlive(bool alive, int type);
	//車が何台生きているかを取得
	int getCarAlive(int type)const;
	//車信号送る
	void setCarSignal(bool carsignal);
	bool getCarSignal()const;
	//歩行者信号送る
	void setCitizenSignal(bool cisignal);
	bool getCitizenSignal()const;
	//エネミーの逃走状態
	void setEnemyEscape(bool escape);
	bool getEnemyEscape()const;
	//車信号送る
	void setCarSignalNum(int car_signal);
	int getCarSignalNum()const;
	//歩行者信号送る
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
	static const int oneroutemax_ = 10;//1ルートの最大人数と台数
	static const int maxtype = 10;//タイプの最大数
	std::list<std::weak_ptr<Actor>> avoidTargets_;
	std::list<std::weak_ptr<Actor>> CitizenList_;
	std::list<std::weak_ptr<Actor>> CarList_;
	bool is_enemy_goal_{ false };
	int score_{ 0 };
	int cialive_[20]{};//市民20パターン(仮)までの配列
	int caralive_[20]{};//車20パターン(仮)までの配列
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