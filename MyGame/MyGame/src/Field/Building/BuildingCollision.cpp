#include "BuildingCollision.h"

// �O�p�`�̏Փ˔���
BuildingCollision::BuildingCollision(const Triangle& triangle, int mode) :
	triangle_(triangle) {
	type_ = ColType::Triangle;
	mode_ = static_cast<ColMode>(mode);
}

// ��`�̏Փ˔���
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
	// �O�p�`�����蔻��`�F�b�N
	Vector3 triVec1, triVec2, triVec3;
	Vector3 hitVec1, hitVec2, hitVec3;
	float   cross1, cross2, cross3;
	bool	hit;

	// �O�p�`�T�C�N���x�N�g��
	triVec1 = subtract(triangle.position[1], triangle.position[0]);
	triVec2 = subtract(triangle.position[2], triangle.position[1]);
	triVec3 = subtract(triangle.position[0], triangle.position[2]);

	// �O�p�`���_����v���C���[�ւ̃x�N�g��
	hitVec1 = subtract(point, triangle.position[0]);
	hitVec2 = subtract(point, triangle.position[1]);
	hitVec3 = subtract(point, triangle.position[2]);

	// ���ꂼ��̊O��
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
	// �O�p�`�����蔻��`�F�b�N
	Vector3 triVec1, triVec2, triVec3;
	Vector3 hitVec1, hitVec2, hitVec3;
	float   cross1, cross2, cross3;
	bool	hit;
	float	fDot;

	// �O�p�`�T�C�N���x�N�g��
	triVec1 = subtract(triangle.position[1], triangle.position[0]);
	triVec2 = subtract(triangle.position[2], triangle.position[1]);
	triVec3 = subtract(triangle.position[0], triangle.position[2]);

	// �T�C�N���x�N�g���P�ʉ�
	triVec1 = triVec1.Normalize();
	triVec2 = triVec2.Normalize();
	triVec3 = triVec3.Normalize();

	// �O�p�`���_����v���C���[�ւ̃x�N�g��
	hitVec1 = subtract(point, triangle.position[0]);
	hitVec2 = subtract(point, triangle.position[1]);
	hitVec3 = subtract(point, triangle.position[2]);

	// ���ꂼ��̊O��
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
		// �v���C���[�ʒu����
		if ((fabsf(cross1) <= fabsf(cross2)) &&
			(fabsf(cross1) <= fabsf(cross3))) {
			// ��1�Ɉ�ԋ߂�
			fDot = Vector3::Dot(triVec1, hitVec1);
			point.x = triVec1.x * fDot + triangle.position[0].x;
			point.z = triVec1.z * fDot + triangle.position[0].z;
		}
		else {
			if (fabsf(cross2) <= fabsf(cross3)) {
				// ��2�Ɉ�ԋ߂�
				fDot = Vector3::Dot(triVec2, hitVec2);
				point.x = triVec2.x * fDot + triangle.position[1].x;
				point.z = triVec2.z * fDot + triangle.position[1].z;
			}
			else {
				// ��3�Ɉ�ԋ߂�
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
	//const float epsilon = -1.0e-5f;	// �덷�z���p�̔����Ȓl
	//Vector3 	LayV;		// �����̏I�_���n�_
	//Vector3 	tls;		// �O�p�`�̒��_0�������̎n�_
	//Vector3 	tle;		// �O�p�`�̒��_0�������̏I�_
	//float 	distl0;
	//float 	distl1;
	//float 	dp;
	//float 	denom;
	//float 	t;
	//Vector3	s;			// �����ƕ��ʂƂ̌�_
	//Vector3 	st0;		// ��_���O�p�`�̒��_0
	//Vector3 	st1;		// ��_���O�p�`�̒��_1
	//Vector3 	st2;		// ��_���O�p�`�̒��_2
	//Vector3 	t01;		// �O�p�`�̒��_0�����_1
	//Vector3 	t12;		// �O�p�`�̒��_1�����_2
	//Vector3 	t20;		// �O�p�`�̒��_2�����_0
	//Vector3	m;

	//// �����̎n�_���O�p�n�̗����ɂ���΁A������Ȃ�
	//tls = firstPos - secondPos;
	////distl0 = tls.Dot(_triangle.Normal);	// �����̎n�_�ƕ��ʂ̋���
	//if (distl0 <= epsilon) return false;

	//// �����̏I�_���O�p�n�̕\���ɂ���΁A������Ȃ�
	//tle = secondPos - triangles_[0].position;
	//distl1 = tle.Dot(_triangle.Normal);	// �����̏I�_�ƕ��ʂ̋���
	//if (distl1 >= -epsilon) return false;

	//// �����ƕ��ʂƂ̌�_s�����
	//denom = distl0 - distl1;
	//t = distl0 / denom;
	//LayV = _segment.end - _segment.start;	// �����̕����x�N�g�����擾
	//s = t * LayV + _segment.start;

	//// ��_���O�p�`�̓����ɂ��邩�ǂ����𒲂ׂ�B
	//// �O�p�`�̓����ɂ���ꍇ�A��_����e���_�ւ̃x�N�g���Ɗe�Ӄx�N�g���̊O�ρi�O�g�j���A�S�Ė@���Ɠ�������������
	//// ��ł���������v���Ȃ���΁A������Ȃ��B
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
	//	*_inter = s;	// ��_���R�s�[
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
