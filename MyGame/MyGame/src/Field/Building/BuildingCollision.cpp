#include "BuildingCollision.h"

// 三角形の衝突判定
BuildingCollision::BuildingCollision(const Triangle& triangle, int mode) :
	triangle_(triangle) {
	type_ = ColType::Triangle;
	mode_ = static_cast<ColMode>(mode);
}

// 矩形の衝突判定
BuildingCollision::BuildingCollision(const Vector3& center, Vector3 min, Vector3 max, int mode) :
	hitPolygonCenter_(center), min_(min), max_(max){
	triangles_[0] = Triangle(center + Vector3(min.x, 0, min.z), center + Vector3(min.x, 0, max.z), center + Vector3(max.x, 0, min.z));
	triangles_[1] = Triangle(center + Vector3(min.x, 0, max.z), center + Vector3(min.x, 0, min.z), center + Vector3(max.x, 0, max.z));
	triangles_[2] = Triangle(center + Vector3(max.x, 0, max.z), center + Vector3(min.x, 0, max.z), center + Vector3(max.x, 0, min.z));
	triangles_[3] = Triangle(center + Vector3(max.x, 0, min.z), center + Vector3(min.x, 0, min.z), center + Vector3(max.x, 0, max.z));
	type_ = ColType::Rectangle;
	mode_ = static_cast<ColMode>(mode);
}

BuildingCollision BuildingCollision::translate(const Vector3& position) const {
	switch (type_)
	{
	case BuildingCollision::ColType::Triangle:
		return BuildingCollision(Triangle(triangle_.position[0] + position, triangle_.position[1] + position, triangle_.position[2] + position));
		break;
	case BuildingCollision::ColType::Rectangle:
		return BuildingCollision(position, min_, max_);
		break;
	}
	return BuildingCollision();
}

BuildingCollision BuildingCollision::transform(const Matrix& matrix){
	setRotation(matrix);
	switch (type_)
	{
	case BuildingCollision::ColType::Triangle:
		return BuildingCollision(Triangle(triangle_.position[0] * matrix.RotationMatrix(), triangle_.position[1] * matrix.RotationMatrix(), triangle_.position[2] * matrix.RotationMatrix()));
		break;
	case BuildingCollision::ColType::Rectangle:
		return BuildingCollision(matrix.Translation(), min_ * matrix.RotationMatrix(), max_ * matrix.RotationMatrix());
		break;
	}
	return BuildingCollision();
}

void BuildingCollision::setRotation(Matrix matrix) {
	rotation_ = matrix;
}

bool BuildingCollision::triHitCheck(const Triangle& triangle, Vector3& point) {
	// 三角形当たり判定チェック
	Vector3 triVec1, triVec2, triVec3;
	Vector3 hitVec1, hitVec2, hitVec3;
	float   cross1, cross2, cross3;
	bool	hit;

	// 三角形サイクルベクトル
	triVec1 = subtract(triangle.position[1], triangle.position[0]);
	triVec2 = subtract(triangle.position[2], triangle.position[1]);
	triVec3 = subtract(triangle.position[0], triangle.position[2]);

	// 三角形頂点からプレイヤーへのベクトル
	hitVec1 = subtract(point, triangle.position[0]);
	hitVec2 = subtract(point, triangle.position[1]);
	hitVec3 = subtract(point, triangle.position[2]);

	// それぞれの外積
	cross1 = triVec1.z * hitVec1.x - triVec1.x * hitVec1.z;
	cross2 = triVec2.z * hitVec2.x - triVec2.x * hitVec2.z;
	cross3 = triVec3.z * hitVec3.x - triVec3.x * hitVec3.z;

	hit = false;

	if (cross1 >= 0.0f) {
		if ((cross2 >= 0.0f) && (cross3 >= 0.0f)) {
			hit = true;
		}
	}
	else {
		if ((cross2 < 0.0f) && (cross3 < 0.0f)) {
			hit = true;
		}
	}

	return hit;
}

bool BuildingCollision::triHitCheck(Vector3& point) {
	return triHitCheck(triangle_, point);
}

bool BuildingCollision::triHitCheckAndNoEntry(const Triangle& triangle, Vector3& point) {
	// 三角形当たり判定チェック
	Vector3 triVec1, triVec2, triVec3;
	Vector3 hitVec1, hitVec2, hitVec3;
	float   cross1, cross2, cross3;
	bool	hit;
	float	fDot;

	// 三角形サイクルベクトル
	triVec1 = subtract(triangle.position[1], triangle.position[0]);
	triVec2 = subtract(triangle.position[2], triangle.position[1]);
	triVec3 = subtract(triangle.position[0], triangle.position[2]);

	// サイクルベクトル単位化
	triVec1 = triVec1.Normalize();
	triVec2 = triVec2.Normalize();
	triVec3 = triVec3.Normalize();

	// 三角形頂点からプレイヤーへのベクトル
	hitVec1 = subtract(point, triangle.position[0]);
	hitVec2 = subtract(point, triangle.position[1]);
	hitVec3 = subtract(point, triangle.position[2]);

	// それぞれの外積
	cross1 = triVec1.z * hitVec1.x - triVec1.x * hitVec1.z;
	cross2 = triVec2.z * hitVec2.x - triVec2.x * hitVec2.z;
	cross3 = triVec3.z * hitVec3.x - triVec3.x * hitVec3.z;

	hit = false;

	if (cross1 >= 0.0f) {
		if ((cross2 >= 0.0f) && (cross3 >= 0.0f)) {
			hit = true;
		}
	}
	else {
		if ((cross2 < 0.0f) && (cross3 < 0.0f)) {
			hit = true;
		}
	}

	if (hit == true) {
		// プレイヤー位置制御
		if ((fabsf(cross1) <= fabsf(cross2)) &&
			(fabsf(cross1) <= fabsf(cross3))) {
			// 辺1に一番近い
			fDot = Vector3::Dot(triVec1, hitVec1);
			point.x = triVec1.x * fDot + triangle.position[0].x;
			point.z = triVec1.z * fDot + triangle.position[0].z;
		}
		else {
			if (fabsf(cross2) <= fabsf(cross3)) {
				// 辺2に一番近い
				fDot = Vector3::Dot(triVec2, hitVec2);
				point.x = triVec2.x * fDot + triangle.position[1].x;
				point.z = triVec2.z * fDot + triangle.position[1].z;
			}
			else {
				// 辺3に一番近い
				fDot = Vector3::Dot(triVec3, hitVec3);
				point.x = triVec3.x * fDot + triangle.position[2].x;
				point.z = triVec3.z * fDot + triangle.position[2].z;
			}
		}
	}

	return hit;
}

bool BuildingCollision::triHitCheckAndNoEntry(Vector3& point) {
	return triHitCheckAndNoEntry(triangle_, point);
}

bool BuildingCollision::recHitCheck(Vector3& point) {
	bool hit[4];

	hit[0] = triHitCheck(triangles_[0], point);
	hit[1] = triHitCheck(triangles_[1], point);
	hit[2] = triHitCheck(triangles_[2], point);
	hit[3] = triHitCheck(triangles_[3], point);

	return (hit[0] || hit[1] || hit[2] || hit[3]);
}

bool BuildingCollision::recHitCheckAndNoEntry(Vector3& point) {	
	bool hit[4];

	hit[0] = triHitCheckAndNoEntry(triangles_[0], point);
	hit[1] = triHitCheckAndNoEntry(triangles_[1], point);
	hit[2] = triHitCheckAndNoEntry(triangles_[2], point);
	hit[3] = triHitCheckAndNoEntry(triangles_[3], point);

	return (hit[0] || hit[1] || hit[2] || hit[3]);
}

bool BuildingCollision::hitCheck(Vector3& point) {
	switch (type_)
	{
	case BuildingCollision::ColType::Triangle:
		return triHitCheck(point);
		break;
	case BuildingCollision::ColType::Rectangle:
		return recHitCheck(point);
		break;
	}
	return false;
}

bool BuildingCollision::hitCheckAndNoEntry(Vector3& point) {
	switch (type_)
	{
	case BuildingCollision::ColType::Triangle:
		return triHitCheckAndNoEntry(point);
		break;
	case BuildingCollision::ColType::Rectangle:
		return recHitCheckAndNoEntry(point);
		break;
	}
	return false;
}

bool BuildingCollision::check(Vector3& point) {
	switch (mode_)
	{
	case BuildingCollision::ColMode::Through:
		return hitCheck(point);
		break;
	case BuildingCollision::ColMode::BlockAll:
		return hitCheckAndNoEntry(point);
		break;
	}

	return false;
}

bool BuildingCollision::checkToLine(Vector3 firstPos, Vector3 secondPos)
{
	//const float epsilon = -1.0e-5f;	// 誤差吸収用の微小な値
	//Vector3 	LayV;		// 線分の終点→始点
	//Vector3 	tls;		// 三角形の頂点0→線分の始点
	//Vector3 	tle;		// 三角形の頂点0→線分の終点
	//float 	distl0;
	//float 	distl1;
	//float 	dp;
	//float 	denom;
	//float 	t;
	//Vector3	s;			// 直線と平面との交点
	//Vector3 	st0;		// 交点→三角形の頂点0
	//Vector3 	st1;		// 交点→三角形の頂点1
	//Vector3 	st2;		// 交点→三角形の頂点2
	//Vector3 	t01;		// 三角形の頂点0→頂点1
	//Vector3 	t12;		// 三角形の頂点1→頂点2
	//Vector3 	t20;		// 三角形の頂点2→頂点0
	//Vector3	m;

	//// 線分の始点が三角系の裏側にあれば、当たらない
	//tls = firstPos - secondPos;
	////distl0 = tls.Dot(_triangle.Normal);	// 線分の始点と平面の距離
	//if (distl0 <= epsilon) return false;

	//// 線分の終点が三角系の表側にあれば、当たらない
	//tle = secondPos - triangles_[0].position;
	//distl1 = tle.Dot(_triangle.Normal);	// 線分の終点と平面の距離
	//if (distl1 >= -epsilon) return false;

	//// 直線と平面との交点sを取る
	//denom = distl0 - distl1;
	//t = distl0 / denom;
	//LayV = _segment.end - _segment.start;	// 線分の方向ベクトルを取得
	//s = t * LayV + _segment.start;

	//// 交点が三角形の内側にあるかどうかを調べる。
	//// 三角形の内側にある場合、交点から各頂点へのベクトルと各辺ベクトルの外積（三組）が、全て法線と同じ方向を向く
	//// 一つでも方向が一致しなければ、当たらない。
	//st0 = _triangle.P0 - s;
	//t01 = _triangle.P1 - _triangle.P0;
	//m = st0.Cross(t01);
	//dp = m.Dot(_triangle.Normal);
	//if (dp <= epsilon) return false;

	//st1 = _triangle.P1 - s;
	//t12 = _triangle.P2 - _triangle.P1;
	//m = st1.Cross(t12);
	//dp = m.Dot(_triangle.Normal);
	//if (dp <= epsilon) return false;

	//st2 = _triangle.P2 - s;
	//t20 = _triangle.P0 - _triangle.P2;
	//m = st2.Cross(t20);
	//dp = m.Dot(_triangle.Normal);
	//if (dp <= epsilon) return false;

	//if (_inter)
	//{
	//	*_inter = s;	// 交点をコピー
	//}

	//return true;

	return false;
}

Vector3 BuildingCollision::subtract(const Vector3& vec1, const Vector3& vec2) {
	return Vector3(vec1.x - vec2.x,
				   vec1.y - vec2.y,
				   vec1.z - vec2.z);
}

Vector3 BuildingCollision::normalize(const Vector3& vec) {
	float length;

	length = sqrtf(vec.x * vec.x +
				   vec.y * vec.y +
				   vec.z * vec.z);

	return Vector3(vec.x / length, vec.y / length, vec.z / length);
}

float BuildingCollision::dot(const Vector3& vec1, const Vector3& vec2) {
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
