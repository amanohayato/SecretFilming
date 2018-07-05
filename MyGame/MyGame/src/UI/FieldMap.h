#pragma once
#include"UI.h"
#include<list>
#include<vector>
#include<memory>
#include"../ID/EnumIDs.h"
#include"../Math/Vector3.h"

class IWorld;
class BuildingBase;
class FieldMap{
public:
	FieldMap(IWorld* world);
	
	//初期化
	void initialize();
	//更新
	void update(float deltaTime);
	//描画
	void draw(const Vector2 & position) const;

	void pin_reset();//全ピンリセット
	void targetpin_reset();//赤ピンの打ち直し

	void pin_add(float deltaTime);//ピンの位置を進める
private:
	IWorld* world_;
	int colorSin_{ 0 };//ターゲットボックスの色変え
	float pinPosRate_{ 0.0f };//ピンの位置割合
	float targetPinRate_{ 0.0f };//赤ピンの位置割合
	int evpCount_{ 0 };//イベントポイント数保持
	std::list<std::weak_ptr<BuildingBase>> buildings_;
	std::list < std::tuple < SPRITE_ID, SPRITE_ID, Vector3>> drawIconList_;

};