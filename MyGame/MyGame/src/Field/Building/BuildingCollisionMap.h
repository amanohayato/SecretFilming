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
	//������(�T�C�Y�̌���)
	void initialize(int xSize,int zSize);
	//�v�f�̒ǉ�
	void add(const BuildingPtr& building, int xBlock, int zBlock);
	//�v�f�̃N���A
	void clear();
	//�����؂�̌����|�C���^���폜����
	void remove_expired();

	std::list<std::weak_ptr<BuildingBase>>& getBuildingList(int x, int z);

	std::list<std::weak_ptr<BuildingBase>> getBuildingLists(int xcell, int zcell, int range);
	std::list<std::weak_ptr<BuildingBase>> getBuildingLists(const Vector3& position, int range);

	Point getcellPosition(const Vector3& position);

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);

private:
	//�����̓����蔻��敪��
	TwoDimensionalArray<std::list<std::weak_ptr<BuildingBase>>> buildingCollisionMap_{};

};
