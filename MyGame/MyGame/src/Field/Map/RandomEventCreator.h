#pragma once
#include"../Building/BuildingBase.h"
#include"../../Math/Point.h"
#include<utility>
#include<array>


class RandomEventCreator {
public:
	RandomEventCreator();

	void initialize(const Point& fieldSize);
	void add(const Vector3& position,std::weak_ptr<BuildingBase> building);

	void chooseEvent(IWorld* world);
	
private:
	std::array<int, 6> eventRoute_{
		1,2,3,4,5,6
	};
	std::list<std::pair<int,EventPoint>> events_;

	Point fieldSize_;
};