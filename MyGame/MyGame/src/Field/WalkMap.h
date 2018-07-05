#pragma once
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"

class WalkMap {
public:
	WalkMap();
	void initialize();
	//csvファイルの読み込み
	void load(const std::string& pointfilename, const std::string& mapfilename);
	//目的地にたどり着くための次の地点を検索する
	int getNextWalkPoint(int target,int current, int goal);
	//地点の座標を取得する
	Vector3 getPosition(int target,int point)const;
	int getSize(int target)const;
	int getNearestPoint(int target,const Vector3& position);

private:
	int size{ 0 };
	std::vector<TwoDimensionalArray<int>> walkPointMap_;//車が目的地に到達するための経路を保存するマップ
	std::vector<std::vector<Vector3>> walkPoints_;//道路ポイントリスト

};