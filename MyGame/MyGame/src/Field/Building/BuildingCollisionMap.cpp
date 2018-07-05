#include "BuildingCollisionMap.h"
#include"../../Math/Vector3.h"
#include "../../Actor/Body/Ray.h"
#include"BuildingBase.h"

#include <map>
#include <vector>
#include<numeric>


bool operator == (std::weak_ptr<BuildingBase>& bptr1, std::weak_ptr<BuildingBase>& bptr2) {
	return bptr1.lock().get() == bptr2.lock().get();
}
bool compbb(std::weak_ptr<BuildingBase>& bptr1, std::weak_ptr<BuildingBase>& bptr2) {
	return bptr1.lock().get() > bptr2.lock().get();
}

BuildingCollisionMap::BuildingCollisionMap()
{
}

void BuildingCollisionMap::initialize(int xSize, int zSize)
{
	buildingCollisionMap_.initialize(xSize, zSize);
}

void BuildingCollisionMap::add(const BuildingPtr & building, int xBlock, int zBlock)
{
	buildingCollisionMap_.getElement(xBlock, zBlock).push_back(building);
}

void BuildingCollisionMap::clear()
{
	buildingCollisionMap_.clear();
}

void BuildingCollisionMap::remove_expired()
{
	buildingCollisionMap_.loopElement([](std::list<std::weak_ptr<BuildingBase>>& building) {
		building.remove_if([](std::weak_ptr<BuildingBase>& building) {return building.expired(); });
	});
}

std::list<std::weak_ptr<BuildingBase>>& BuildingCollisionMap::getBuildingList(int x, int z)
{
	return buildingCollisionMap_.getElement(x, z);
}

std::list<std::weak_ptr<BuildingBase>> BuildingCollisionMap::getBuildingLists(int xcell,int zcell,int range)
{
	std::list<std::weak_ptr<BuildingBase>> result;
	for (int z = -range+1; z < range; z++) {
		for (int x = -range+1; x < range; x++) {
			int xpos = x + xcell;
			int zpos = z + zcell;
			if (xpos >= buildingCollisionMap_.getXSize() ||
				zpos >= buildingCollisionMap_.getYSize() ||
				xpos <0 ||
				zpos <0
				)continue;

			auto buils = getBuildingList(xpos, zpos);
			for (auto& b : buils) {
				result.push_back(b);
			}
		}
	}
	result.sort(compbb);
	result.unique();

	return result;
}

std::list<std::weak_ptr<BuildingBase>> BuildingCollisionMap::getBuildingLists(const Vector3 & position, int range)
{
	auto point = getcellPosition(position);
	//OutputDebugString((std::to_string(point.x)+","+std::to_string(point.y)+"\n").c_str());
	return getBuildingLists(point.x, point.y, range);
}

Point BuildingCollisionMap::getcellPosition(const Vector3 & position)
{
	return Point{
	MathHelper::Clamp((int)floor(position.x/ sliceSize / SQUARES_WIDTH),0,buildingCollisionMap_.getXSize() - 1),
	MathHelper::Clamp(buildingCollisionMap_.getYSize() - (int)floor(position.z/ sliceSize / SQUARES_HEIGHT) - 1,0,buildingCollisionMap_.getYSize() - 1)
	};
}
#include <numeric>
//164�s�ڂ� std::list<std::weak_ptr<BuildingBase>> list ���z��O�Q�Ƃ��Ă܂���
//�`�F�b�N���肢���܂�
bool BuildingCollisionMap::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	/*
	�ŏ��_�A�ő�_��xy�z��͈̔͂����
	�ŏ��_�ɌX���̕��ꕪ�q�����ꂼ��ɑ����Ă���
	�������т�round�Ŋۂ߂��l��z��ɒǉ����Ă���
	�����x,y+-1�͈̔͂Ŏ���Ă���
	*/

	//2�_�̃Z���Ԓn������Ă���
	auto fp = getcellPosition(firstPos);
	auto lp = getcellPosition(secondPos);

	//�X���𒲂ׂ�
	auto slope = lp - fp;
	//�X������Axy�f�J����������Ă���
	int div = abs(slope.x) > abs(slope.y) ? slope.x : slope.y;
	div = abs(div);
	//�X����xy�ɂ��ꂼ��f�J������������A�}�X���Z���Ɏg�p
	float addx = (float)slope.x / div;
	float addy = (float)slope.y / div;

	std::list<Point> cellList{};
	//���[�v�񐔂𒲂ׂ�
	int loopCount = abs(slope.x) > abs(slope.y) ? lp.x - fp.x : lp.y - fp.y;
	loopCount = abs(loopCount);
	loopCount = MathHelper::Abs(loopCount);
	for (int i = 0; i <= loopCount; i++) {
		Point cp;//�Ώۃ}�X
		Point jp;//���Ӄ}�X
		cp.x = fp.x + (int)roundf(addx*i);
		cp.y = fp.y + (int)roundf(addy*i);
		cellList.push_back(cp);
		jp = cp + Point{ 1, 0 };
		cellList.push_back(jp);
		jp = cp + Point{ 0, -1 };
		cellList.push_back(jp);
		jp = cp + Point{ -1, 0 };
		cellList.push_back(jp);
		jp = cp + Point{ 0, 1 };
		cellList.push_back(jp);
	}
	//�d�����͍폜
	cellList.sort([](Point& p1, Point& p2) {return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y); });
	cellList.unique();
	//�͈͊O�}�X���폜
	cellList.remove_if([&](Point& p) {
		return p.x < 0 || p.y < 0 ||
			p.x >= buildingCollisionMap_.getXSize() ||
			p.y >= buildingCollisionMap_.getYSize();
	});
	//�Ώۃ}�X�ɓ����Ă�r����S������Ă���
	std::list<std::weak_ptr<BuildingBase>> buils;
	for (auto cl : cellList) {
		auto bl = getBuildingList(cl.x, cl.y);
		buils.insert(buils.end(), bl.begin(), bl.end());
	}
	//�r���̏d�������폜
	buils.sort(compbb);
	buils.unique();


	for (auto& b : buils) {
		//�Ώۂ̌����̏����X�V
		MV1RefreshCollInfo(b.lock()->getModelHandle());
		//�������f���Ƃ̂����蔻��
		auto HitPoly = MV1CollCheck_Line(b.lock()->getModelHandle(), -1, firstPos, secondPos);
		//�������Ă���true
		if (HitPoly.HitFlag == TRUE) return true;
	}
	//�������ĂȂ�������false
	return false;

	//float minPosX = firstPos.x;
	//float maxPosX = secondPos.x;
	//if (minPosX > secondPos.x) {
	//	minPosX = secondPos.x;
	//	maxPosX = firstPos.x;
	//}
	//float rangeX = maxPosX - minPosX;

	//float minPosZ = firstPos.z;
	//float maxPosZ = secondPos.z;
	//if (minPosZ > secondPos.z) {
	//	minPosZ = secondPos.z;
	//	maxPosZ = firstPos.z;
	//}
	//float rangeZ = maxPosZ - minPosZ;

	//// �����蔻����s�������B
	//std::vector<std::weak_ptr<BuildingBase>> collisionBuildings;

	//// Line �� x �v�f�� z �v�f�ȏ�Ȃ��
	//if (rangeX >= rangeZ)
	//{
	//	// x �̒l����Ƃ��������̌X��
	//	float slope = rangeZ / rangeX;

	//	// x �̒l����ɂ�������
	//	for (int x = 0; x <= (int)rangeX; x++)
	//	{
	//		for (int i = -1; i <= 1; i++)
	//		{
	//			int xlistPos = (int)((minPosX + x) / SQUARES_WIDTH);
	//			int zlistPos = (int)((minPosZ + (x + i) * slope) / SQUARES_WIDTH);
	//			if (
	//				xlistPos >= buildingCollisionMap_.getXSize() ||
	//				xlistPos < 0 ||
	//				zlistPos >= buildingCollisionMap_.getYSize() ||
	//				zlistPos < 0
	//				) {
	//				continue;
	//			}

	//			std::list<std::weak_ptr<BuildingBase>> list =
	//				buildingCollisionMap_.getElement
	//				(xlistPos, zlistPos);

	//			// �Ή������}�X�̌����|�C���^�����������X�g�̎擾
	//			for each (std::weak_ptr<BuildingBase> building in list)
	//			{
	//				// �d���㓙
	//				collisionBuildings.push_back(building);

	//				// �������ł� collisionBuildings �ɒǉ�����Ă��邩�H
	//				// ����N���X���Ǝg�p�ł��Ȃ��H
	//				//auto itr = std::find(collisionBuildings.begin(), collisionBuildings.end(), building);

	//				//// �ǉ�����Ă��Ȃ����
	//				//if (itr == collisionBuildings.end()) 
	//				//{
	//				//	// �ǉ�����
	//				//	collisionBuildings.push_back(building);
	//				//}

	//				// �n�b�V���e�[�u�����ۂ��̎g�����������c
	//				// ����N���X���Ǝg�p�ł��Ȃ��H
	//				//int hash = std::hash<std::weak_ptr<BuildingBase>>()(building);
	//				//// �Ώۂ̌����|�C���^�� collisionBuildings �̃L�[�ɂȂ��Ă��Ȃ����
	//				//if (collisionBuildings.count(std::hash<std::weak_ptr<BuildingBase>>()(building) == 0)) {
	//				//	// collisionBuildings �ɗv�f��ǉ�
	//				//	collisionBuildings[std::hash<std::weak_ptr<BuildingBase>>()(building)] = building;
	//				//}
	//			}
	//		}
	//	}
	//}
	//// �����łȂ����
	//else
	//{
	//	// z �̒l����Ƃ��������̌X��
	//	float slope = rangeX / rangeZ;

	//	// z �̒l����ɂ�������
	//	for (int z = 0; z <= (int)rangeZ; z++)
	//	{
	//		for (int i = -1; i <= 1; i++)
	//		{
	//			int xlistPos = (int)((minPosX + (z + i) * slope) / SQUARES_WIDTH);
	//			int zlistPos = (int)((minPosZ + z) / SQUARES_WIDTH);
	//			if (
	//				xlistPos >= buildingCollisionMap_.getXSize() ||
	//				xlistPos < 0 ||
	//				zlistPos >= buildingCollisionMap_.getYSize() ||
	//				zlistPos < 0
	//				) {
	//				continue;
	//			}
	//			std::list<std::weak_ptr<BuildingBase>> list =
	//				buildingCollisionMap_.getElement
	//				(xlistPos, zlistPos);

	//			// �Ή������}�X�̌����|�C���^�����������X�g�̎擾
	//			for each (std::weak_ptr<BuildingBase> building in list)
	//			{
	//				// �d���㓙
	//				collisionBuildings.push_back(building);
	//			}
	//		}
	//	}
	//}

	//// ray���g����������
	////std::shared_ptr<Ray> ray = std::make_shared<Ray>(firstPos, secondPos - firstPos);

	//// �����蔻����s�������B������
	//for (int i = 0; i < collisionBuildings.size(); i++)
	//{
	//	std::weak_ptr<BuildingBase> ptr = collisionBuildings[i];

	//	if (ptr.lock()->getCollision().checkToLine(firstPos, secondPos)) return true;
	//}

	//return false;
}
