#pragma once
#include<DxLib.h>
#include"../Vector3.h"
#include"../Matrix.h"
#include"CollisionTriangle.h"
#include<cmath>
#include"../../Graphic/DebugDraw.h"
#include"../../Conv/DXConverter.h"

class CollisionMesh {
public:
	CollisionMesh(int model) :model_{ model } {
	}
	//メッシュと線分の当たり判定
	bool collide_line(const VECTOR& start, const VECTOR& end, VECTOR* point = nullptr, VECTOR* normal = nullptr)const {
		//当たっているかを調べて、交点と法線を返す
		const auto coll_poly = MV1CollCheck_Line(model_, 0, start, end);
		//交点と法線データを入れる
		if (coll_poly.HitFlag == TRUE) {
			if (point != nullptr) {
				*point = coll_poly.HitPosition;
			}
			if (normal != nullptr) {
				*normal = coll_poly.Normal;
			}
		}
		return coll_poly.HitFlag == TRUE;
	}
	//メッシュと球体の当たり判定
	bool collide_sphere(const VECTOR& center, float radius, VECTOR* result = nullptr)const {
		//モデルと球体の当たり判定関数、当たった情報を持つ
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//衝突判定データの削除、coll_polyはメモリ確保を動的に行っているため、Poly用のdelete代わりの関数を呼ぶ必要がある
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//平面と点の衝突関係情報の入れ物
			PLANE_POINT_RESULT plane_point_result;
			//無限平面と点の当たり判定を行う、平面上に一番近い点を調べたりしてくれる
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//平面のうち好きな点、平面上であればposition[0]でなくても良い
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//これに無限平面と、自身の点の最も近い点の情報等が入る
				);

			//三角形の中に、無限平面のうち一番近い点が入っているかを調べる=三角形の中に中心点が入っているかを調べる
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//面に当たってたら、面の法線方向に押し出す、大きさはoffset、めり込み分だけ押し出す
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//法線方向に押し出すベクトルの計算
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//ポリゴンと辺の判定
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
				).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	bool collide_sphere(const VECTOR& center,const VECTOR& previous, float radius, VECTOR* result = nullptr)const {
		//モデルと球体の当たり判定関数、当たった情報を持つ
		const auto coll_poly = MV1CollCheck_Sphere(model_, 0, center, radius);
		if (coll_poly.HitNum == 0) {
			//衝突判定データの削除、coll_polyはメモリ確保を動的に行っているため、Poly用のdelete代わりの関数を呼ぶ必要がある
			MV1CollResultPolyDimTerminate(coll_poly);
			return false;
		}
		auto result_center = center;
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			//平面と点の衝突関係情報の入れ物
			PLANE_POINT_RESULT plane_point_result;
			//無限平面と点の当たり判定を行う、平面上に一番近い点を調べたりしてくれる
			Plane_Point_Analyse(
				&coll_poly.Dim[i].Position[0],//平面のうち好きな点、平面上であればposition[0]でなくても良い
				&coll_poly.Dim[i].Normal,
				&result_center,
				&plane_point_result//これに無限平面と、自身の点の最も近い点の情報等が入る
			);

			//三角形の中に、無限平面のうち一番近い点が入っているかを調べる=三角形の中に中心点が入っているかを調べる
			if (CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
			).is_inside(plane_point_result.Plane_MinDist_Pos)) {
				//面に当たってたら、面の法線方向に押し出す、大きさはoffset、めり込み分だけ押し出す
				const auto distance = std::sqrt(plane_point_result.Plane_Pnt_MinDist_Square);
				//法線方向に押し出すベクトルの計算
				const auto offset = VScale(coll_poly.Dim[i].Normal, radius - distance);
				result_center = VAdd(result_center, offset);
			}
		}
		//ポリゴンと辺の判定
		for (int i = 0; i < coll_poly.HitNum; ++i) {
			CollisionTriangle(
				coll_poly.Dim[i].Position[0],
				coll_poly.Dim[i].Position[1],
				coll_poly.Dim[i].Position[2]
			).collide_edge_and_sphere(result_center, radius, &result_center);
		}
		if (result != nullptr) {
			*result = result_center;
		}
		MV1CollResultPolyDimTerminate(coll_poly);
		return true;
	}
	bool collide_capsule(const VECTOR& start, const VECTOR& end, float radius, VECTOR* result = nullptr) {
		//当たったかどうか
		bool isHit = false;

		//始点、終点を取得
		VECTOR resultstart=start;
		VECTOR resultend=end;

		//足元を基準にした押し出し判定を行う
		if (collide_sphere(resultend, radius, &resultend)) {
			//足元からの押し出しベクトルを作成
			Vector3 moveVecbottom = VSub(resultend, end);
			//カプセルの始点に押し出しを適用
			resultstart = VAdd(resultstart, moveVecbottom);
			isHit = true;
		}
		//足元押し出し時点の始点、終点情報を保存
		VECTOR savestart = resultstart;
		VECTOR saveend = resultend;

		//頭を基準にした押し出し判定を行う
		if (collide_sphere(resultstart, radius, &resultstart)) {
			//頭からの押し出しベクトルを作成
			Vector3 moveVectop = VSub(resultstart, savestart);
			//カプセルの終点に押し出しを適用
			resultend = VAdd(resultend, moveVectop);
			isHit = true;
		}
		//ここまでで始点終点の押し出しが完了

		//中心を計算して返す
		//if(isHit)*result = (resultstart+ resultend)*0.5f;

		// プレイヤーの周囲にあるポリゴンを検出した結果が代入される当たり判定結果構造体
		MV1_COLL_RESULT_POLY_DIM HitDim = MV1CollCheck_Capsule(model_, -1, resultstart, resultend, radius);

		for (int i = 0; i < HitDim.HitNum; i++) {
			VECTOR triangle[4]{
				HitDim.Dim[i].Position[0],
				HitDim.Dim[i].Position[1],
				HitDim.Dim[i].Position[2],
				HitDim.Dim[i].Position[0]
			};

			for (int loop = 0; loop < 3; loop++) {
				SEGMENT_SEGMENT_RESULT seg_seg_result;
				Segment_Segment_Analyse(&resultstart, &resultend, &triangle[i], &triangle[i + 1], &seg_seg_result);
				const auto distance = std::sqrt(seg_seg_result.SegA_SegB_MinDist_Square);
				if (distance <= radius) {
					isHit = true;
					VECTOR offset = VScale(VNorm(VSub(seg_seg_result.SegA_MinDist_Pos, seg_seg_result.SegB_MinDist_Pos)), radius - distance);
					resultstart = VAdd(resultstart, offset);
					resultend = VAdd(resultend, offset);
				}
			}
		}
		if (isHit)*result = (resultstart + resultend)*0.5f;

		//ポリゴンを開放する
		MV1CollResultPolyDimTerminate(HitDim);

		return isHit;

	}
	bool collide_capsule(const VECTOR& start1, const VECTOR& end1, float radius1, const VECTOR& start2, const VECTOR& end2, float radius2, VECTOR* result1 = nullptr, VECTOR* result2 = nullptr) {
		//当たったかどうか
		bool isHit = false;

		//始点、終点を取得
		VECTOR resultstart1 = start1;
		VECTOR resultend1 = end1;
		VECTOR resultstart2 = start2;
		VECTOR resultend2 = end2;

		if (collide_sphere(resultend1, radius1, &resultend1)) {
			//足元からの押し出しベクトルを作成
			Vector3 moveVecbottom = VSub(resultend1, end1);
			//カプセルの始点に押し出しを適用
			resultend2 = VAdd(resultend2, moveVecbottom);
			isHit = true;
		}
		if (collide_sphere(resultend2, radius2, &resultend2)) {
			//足元からの押し出しベクトルを作成
			Vector3 moveVecbottom2 = VSub(resultend2, end2);
			//カプセルの始点に押し出しを適用
			resultend1 = VAdd(resultend1, moveVecbottom2);
			isHit = true;
		}

		//中心を計算して返す
		if (isHit) {
			*result1 = resultend1;
			*result2 = resultend2;
		}
		return isHit;

	}

private:
	int model_;
};
