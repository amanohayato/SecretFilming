#pragma once
#include"../World/IWorld.h"
#include"../Resource/CsvReader.h"

class PointGenerator {
public:
	PointGenerator();
	PointGenerator(IWorld* world, const std::string& filename);

	~PointGenerator();

	//値を設定して、初期化する
	void setParameter(IWorld* world, const std::string& filename);

	//ポイント数の監視、ポイントが消えたら次のポイントを生成
	void update(float deltaTime);

	void draw()const;

	bool isEnd()const;
private:
	//ポイント生成
	void generate();
private:
	IWorld* world_{ nullptr };//ワールド
	CsvReader reader_;//CSV読み込み
	int pointCount_{ 0 };//生成したポイント数
	bool isEnd_{ false }; //ポイントを全部取得したら終了

};