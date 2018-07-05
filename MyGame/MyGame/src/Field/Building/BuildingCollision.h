#ifndef C_TRIANGLE_H_
#define C_TRIANGLE_H_

#include <list>

#include "../../Math/Collision/Collision.h"

#define PI	3.1415927f
#define CHECK_POLYGON_ANGLES	4     // ���p�`�̉搔

class BuildingCollision {
public:
	enum class ColType {
		Triangle,		// �O�p�`�̓����蔻��
		Rectangle		// ��`�̓����蔻��
	};
	enum class ColMode {
		Through,		// ���肾��
		BlockAll,		// �i���֎~
		None,			// �����Ȃ�
	};
public:
	BuildingCollision() = default;
	BuildingCollision(const Triangle& triangle, int mode = 1);
	BuildingCollision(const Vector3& center, Vector3 min, Vector3 max, int mode = 1);

	BuildingCollision translate(const Vector3& position) const;
	BuildingCollision transform(const Matrix& matrix);

	void setRotation(Matrix matrix);

	bool triHitCheck(const Triangle& triangle, Vector3& point);
	bool triHitCheck(Vector3& point);
	bool triHitCheckAndNoEntry(const Triangle& triangle, Vector3& point);
	bool triHitCheckAndNoEntry(Vector3& point);
	bool recHitCheck(Vector3& point);
	bool recHitCheckAndNoEntry(Vector3& point);

	bool hitCheck(Vector3& point);
	bool hitCheckAndNoEntry(Vector3& point);

	bool check(Vector3& point);

	bool checkToLine(Vector3 firstPos, Vector3 secondPos);

private:
	Vector3 subtract(const Vector3& vec1, const Vector3& vec2);
	Vector3 normalize(const Vector3& vec);
	float dot(const Vector3& vec1, const Vector3& vec2);

private:
	Triangle triangle_{ Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f) };

	Triangle triangles_[CHECK_POLYGON_ANGLES];

	Matrix  rotation_{ Matrix::Identity };

	Vector3 hitPolygonCenter_{ 0.0f, 0.0f, 0.0f };

	Vector3 min_;
	Vector3 max_;

	ColType type_;
	ColMode mode_;
};

#endif // !C_TRIANGLE_H_

