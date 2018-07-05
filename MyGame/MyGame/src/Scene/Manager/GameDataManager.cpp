#include "GameDataManager.h"
//#include "../../ID/EnumIDs.h"

void GameDataManager::initialize()
{
	avoidTargets_.clear();
	CarList_.clear();
	CitizenList_.clear();
	is_enemy_goal_ = false;
	escape_ = false;
	carsignal_ = true;
	cisignal_ = false;
	ci_signal_ = 0;
	car_signal_ = 2;
	is_game_stop_ = false;
	mapSize_ = Vector2::Zero;
	score_ = 0;

	escapeCount_ = 0;
	photoCount_ = 0;

	/*
	for (int i = 0; i < maxtype; i++) {
		citizencount_[i] = 0;
		carcount_[i] = 0;
	}*/
	
}

void GameDataManager::addAvoidTarget(ActorPtr ptr)
{
	avoidTargets_.push_back(ptr);
}

void GameDataManager::removeAvoidTarget(const ActorPtr & ptr)
{
	avoidTargets_.remove_if([&](auto& at) {
		return ptr.get() == at.lock().get();
	});
}

std::list<std::weak_ptr<Actor>> GameDataManager::getAvoidTarget() const
{
	return avoidTargets_;
}

void GameDataManager::addCarList(ActorPtr ptr)
{
	CarList_.push_back(ptr);
}

void GameDataManager::removeCarList(const ActorPtr & ptr)
{
	CarList_.remove_if([&](auto& at) {
		return ptr.get() == at.lock().get();
	});
}

std::list<std::weak_ptr<Actor>> GameDataManager::getCarList() const
{
	return CarList_;
}

void GameDataManager::addCitizenList(ActorPtr ptr)
{
	CitizenList_.push_back(ptr);
}

void GameDataManager::removeCitizenList(const ActorPtr & ptr)
{
	CitizenList_.remove_if([&](auto& at) {
		return ptr.get() == at.lock().get();
	});
}

std::list<std::weak_ptr<Actor>> GameDataManager::getCitizenList() const
{
	return CitizenList_;
}

// エネミーのゴール到達判定を設定
void GameDataManager::setEnemyGoal(bool is_goal)
{
	is_enemy_goal_ = is_goal;
}

// エネミーのゴール到達判定を取得
bool GameDataManager::getEnemyGoal() const
{
	return is_enemy_goal_;
}

void GameDataManager::setScore(int score)
{
	score_ = score;
}

int GameDataManager::getScore() const
{
	return score_;
}

void GameDataManager::setCiAlive(bool alive, int type)
{
	if (alive)
	{
		cialive_[type]++;
	}
	else if (!alive && cialive_[type] != 0)
	{
		cialive_[type]--;
	}
}
int GameDataManager::getCiAlive(int type) const
{
	return cialive_[type];
}
void GameDataManager::setCarAlive(bool alive, int type)
{
	if (alive)
	{
		caralive_[type]++;
	}
	else if (!alive && caralive_[type] != 0)
	{
		caralive_[type]--;
	}
}
int GameDataManager::getCarAlive(int type) const
{
	return caralive_[type];
}
void GameDataManager::setCarSignal(bool carsignal)
{
	carsignal_ = carsignal;
}
bool GameDataManager::getCarSignal() const
{
	return carsignal_;
}
void GameDataManager::setCitizenSignal(bool cisignal)
{
	cisignal_ = cisignal;
}
bool GameDataManager::getCitizenSignal() const
{
	return cisignal_;
}
void GameDataManager::setEnemyEscape(bool escape)
{
	escape_ = escape;
}
bool GameDataManager::getEnemyEscape() const
{
	return escape_;
}

void GameDataManager::setCarSignalNum(int car_signal)
{
	car_signal_ = car_signal;
}

int GameDataManager::getCarSignalNum() const
{
	return car_signal_;
}

void GameDataManager::setCitizenSignalNum(int ci_signal)
{
	ci_signal_ = ci_signal;
}

int GameDataManager::getCitizenSignalNum() const
{
	return ci_signal_;
}

Vector2 GameDataManager::getMapSize() const
{
	return mapSize_;
}

void GameDataManager::setMapSize(const Vector2 & size)
{
	mapSize_ = size;
}

float GameDataManager::getCameraSens() const
{
	return cameraSens_;
}

void GameDataManager::setCameraSens(float value)
{
	cameraSens_ = value;
}

bool GameDataManager::getGameStop() const
{
	return is_game_stop_;
}

void GameDataManager::setGameStop(bool is_game_stop)
{
	is_game_stop_ = is_game_stop;
}

int GameDataManager::getEscapeCount()
{
	return escapeCount_;
}

void GameDataManager::addEscapeCount(int value)
{
	escapeCount_ += value;
}

int GameDataManager::getPhotoCount()
{
	return photoCount_;
}

void GameDataManager::addPhotoCount(int value)
{
	photoCount_ += value;

	if (photoCount_ > 999) photoCount_ = 999;
}


