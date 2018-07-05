#pragma once
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"

class IWorld;//テスト用
class CityMap {
public:
	CityMap();
	~CityMap();
	void initialize();
	//csvファイルの読み込み
	void load(const std::string& filename, const std::string& mapfilename);
	//目的地にたどり着くための次の地点を検索する
	int getNextCarPoint(int current,int goal);
	//地点の座標を取得する
	Vector3 getPosition(int point)const;
	void getWorld(IWorld* wrd);//テスト
	int getSize()const;
	int getNearestPoint(const Vector3& position);
	float getFlyPointY(int indexNum)const;
	void draw()const;//デバッグ表示
private:
	TwoDimensionalArray<int> carPointMap_;//車が目的地に到達するための経路を保存するマップ
	std::vector<Vector3> carPoints_;//道路ポイントリスト
	std::vector<float> flyPointsy_;//飛行用y軸座標リスト
	IWorld* world;//テスト用ワールド
};