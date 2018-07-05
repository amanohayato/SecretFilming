#pragma once
#include "../../Math/Collision/CollisionMesh.h"
#include "../../ID/EnumIDs.h"
#include"FloorTilingMap.h"
//#include "../../../Field/FieldOut.h"
#include"../../Math/TwoDimensionalArray.h"

// フィールド（オンリー）クラス
class Field {
public:
	// コンストラクタ
	Field(int field = -1);
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	void shadowDraw()const;
	// フィールドのハンドル取得
	int modelHandle(); // Probably no longer needed?
	CollisionMesh& getMesh();
	// コピー禁止
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

	int getFloorTile(int x,int y) const;

	int getWidth()const;
	int getHeight()const;
private:
	int field_;
	CollisionMesh mesh_;

	FloorTilingMap ftm_{};

};