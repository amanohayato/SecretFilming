#include "WalkMap.h"
#include"../Resource/CsvReader.h"
#include"../Actor/Actor.h"

WalkMap::WalkMap()
{
}

void WalkMap::initialize()
{
	walkPoints_.clear();
	walkPointMap_.clear();
	size = 0;
}

void WalkMap::load(const std::string & pointfilename, const std::string & mapfilename)
{
	size++;
	CsvReader cr{ pointfilename };

	walkPoints_.emplace_back();
	for (int i = 0; i < cr.rows(); i++) {
		//歩行者用の地上座標を取得
		walkPoints_.back().emplace_back(
			cr.getf(i, 0),
			cr.getf(i, 1),
			cr.getf(i, 2)
		);
	}
	cr.load(mapfilename);

	walkPointMap_.emplace_back();
	walkPointMap_.back().initialize(cr.columns(), cr.rows());

	for (int r = 0; r < cr.rows(); r++) {
		for (int c = 0; c < cr.columns(); c++) {
			int x = cr.geti(r, c);
			walkPointMap_.back().setElement(c, r, x);//経路マップを設定していく
		}
	}

}

int WalkMap::getNextWalkPoint(int target,int current, int goal)
{
	if (target >= size)return -1;
	return walkPointMap_.at(target).getElement(current, goal);
}

Vector3 WalkMap::getPosition(int target,int point) const
{
	if (target >= size)return Vector3::Zero;
	return walkPoints_.at(target)[point];
}

int WalkMap::getSize(int target) const
{
	if (target >= size)return -1;
	return (int)walkPoints_.at(target).size();
}

int WalkMap::getNearestPoint(int target,const Vector3 & position)
{
	if (target >= size)return -1;

	int result = 0;
	float nearlength = Vector3::Distance(position, walkPoints_.at(target).front());

	float length;
	for (int i = 0; i < walkPoints_.at(target).size(); i++) {
		if (target >= size)return -1;
		length = Vector3::Distance(position, walkPoints_.at(target).at(i));
		if (length < nearlength) {
			nearlength = length;
			result = i;
		}
	}
	return result;

}


