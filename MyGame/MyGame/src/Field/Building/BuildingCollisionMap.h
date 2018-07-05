#pragma once
#include<memory>
#include<list>

#include"../../Math/TwoDimensionalArray.h"
#include"BuildingPtr.h"
#include"../../Math/Point.h"

struct Vector3;

class BuildingCollisionMap
{
public:
	BuildingCollisionMap();
	//初期化(サイズの決定)
	void initialize(int xSize,int zSize);
	//要素の追加
	void add(const BuildingPtr& building, int xBlock, int zBlock);
	//要素のクリア
	void clear();
	//期限切れの建物ポインタを削除する
	void remove_expired();

	std::list<std::weak_ptr<BuildingBase>>& getBuildingList(int x, int z);

	std::list<std::weak_ptr<BuildingBase>> getBuildingLists(int xcell, int zcell, int range);
	std::list<std::weak_ptr<BuildingBase>> getBuildingLists(const Vector3& position, int range);

	Point getcellPosition(const Vector3& position);

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);

private:
	//建物の当たり判定区分け
	TwoDimensionalArray<std::list<std::weak_ptr<BuildingBase>>> buildingCollisionMap_{};

};
