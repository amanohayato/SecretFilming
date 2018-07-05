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
//164行目の std::list<std::weak_ptr<BuildingBase>> list が配列外参照してました
//チェックお願いします
bool BuildingCollisionMap::hitToLine(Vector3 firstPos, Vector3 secondPos)
{
	/*
	最小点、最大点でxy配列の範囲を取る
	最小点に傾きの分母分子をそれぞれに足していく
	足すたびにroundで丸めた値を配列に追加していき
	これをx,y+-1の範囲で取っていく
	*/

	//2点のセル番地を取ってくる
	auto fp = getcellPosition(firstPos);
	auto lp = getcellPosition(secondPos);

	//傾きを調べる
	auto slope = lp - fp;
	//傾きから、xyデカい方を取ってくる
	int div = abs(slope.x) > abs(slope.y) ? slope.x : slope.y;
	div = abs(div);
	//傾きのxyにそれぞれデカい方をかける、マス加算時に使用
	float addx = (float)slope.x / div;
	float addy = (float)slope.y / div;

	std::list<Point> cellList{};
	//ループ回数を調べる
	int loopCount = abs(slope.x) > abs(slope.y) ? lp.x - fp.x : lp.y - fp.y;
	loopCount = abs(loopCount);
	loopCount = MathHelper::Abs(loopCount);
	for (int i = 0; i <= loopCount; i++) {
		Point cp;//対象マス
		Point jp;//周辺マス
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
	//重複分は削除
	cellList.sort([](Point& p1, Point& p2) {return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y); });
	cellList.unique();
	//範囲外マスも削除
	cellList.remove_if([&](Point& p) {
		return p.x < 0 || p.y < 0 ||
			p.x >= buildingCollisionMap_.getXSize() ||
			p.y >= buildingCollisionMap_.getYSize();
	});
	//対象マスに入ってるビルを全部取ってくる
	std::list<std::weak_ptr<BuildingBase>> buils;
	for (auto cl : cellList) {
		auto bl = getBuildingList(cl.x, cl.y);
		buils.insert(buils.end(), bl.begin(), bl.end());
	}
	//ビルの重複分を削除
	buils.sort(compbb);
	buils.unique();


	for (auto& b : buils) {
		//対象の建物の情報を更新
		MV1RefreshCollInfo(b.lock()->getModelHandle());
		//建物モデルとのあたり判定
		auto HitPoly = MV1CollCheck_Line(b.lock()->getModelHandle(), -1, firstPos, secondPos);
		//当たってたらtrue
		if (HitPoly.HitFlag == TRUE) return true;
	}
	//当たってなかったらfalse
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

	//// 当たり判定を行う建物達
	//std::vector<std::weak_ptr<BuildingBase>> collisionBuildings;

	//// Line の x 要素が z 要素以上ならば
	//if (rangeX >= rangeZ)
	//{
	//	// x の値を基準とした線分の傾き
	//	float slope = rangeZ / rangeX;

	//	// x の値を基準にした処理
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

	//			// 対応したマスの建物ポインタが入ったリストの取得
	//			for each (std::weak_ptr<BuildingBase> building in list)
	//			{
	//				// 重複上等
	//				collisionBuildings.push_back(building);

	//				// もうすでに collisionBuildings に追加されているか？
	//				// 自作クラスだと使用できない？
	//				//auto itr = std::find(collisionBuildings.begin(), collisionBuildings.end(), building);

	//				//// 追加されていなければ
	//				//if (itr == collisionBuildings.end()) 
	//				//{
	//				//	// 追加する
	//				//	collisionBuildings.push_back(building);
	//				//}

	//				// ハッシュテーブルっぽいの使いたかった…
	//				// 自作クラスだと使用できない？
	//				//int hash = std::hash<std::weak_ptr<BuildingBase>>()(building);
	//				//// 対象の建物ポインタが collisionBuildings のキーになっていなければ
	//				//if (collisionBuildings.count(std::hash<std::weak_ptr<BuildingBase>>()(building) == 0)) {
	//				//	// collisionBuildings に要素を追加
	//				//	collisionBuildings[std::hash<std::weak_ptr<BuildingBase>>()(building)] = building;
	//				//}
	//			}
	//		}
	//	}
	//}
	//// そうでなければ
	//else
	//{
	//	// z の値を基準とした線分の傾き
	//	float slope = rangeX / rangeZ;

	//	// z の値を基準にした処理
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

	//			// 対応したマスの建物ポインタが入ったリストの取得
	//			for each (std::weak_ptr<BuildingBase> building in list)
	//			{
	//				// 重複上等
	//				collisionBuildings.push_back(building);
	//			}
	//		}
	//	}
	//}

	//// rayを使いたかった
	////std::shared_ptr<Ray> ray = std::make_shared<Ray>(firstPos, secondPos - firstPos);

	//// 当たり判定を行う建物達を巡回
	//for (int i = 0; i < collisionBuildings.size(); i++)
	//{
	//	std::weak_ptr<BuildingBase> ptr = collisionBuildings[i];

	//	if (ptr.lock()->getCollision().checkToLine(firstPos, secondPos)) return true;
	//}

	//return false;
}
