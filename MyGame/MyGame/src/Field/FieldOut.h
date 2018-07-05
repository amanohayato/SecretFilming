#pragma once
#include"../Math/Collision/CollisionMesh.h"

//範囲外チェック用当たり判定保持クラス
class FieldOut {
public:
	FieldOut(int handle);

	CollisionMesh mesh_;

};