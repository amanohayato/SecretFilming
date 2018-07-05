#include "Matrix2D.h"
#include"MathHelper.h"

Matrix2D::Matrix2D():mat_(2,2,1.0f,0.0f,0.0f,1.0f)
{

}

Matrix2D::Matrix2D(float x1, float x2, float y1, float y2):mat_(2,2,x1,x2,y1,y2)
{
}

Matrix2D::~Matrix2D()
{
}

Vector2 Matrix2D::transform(const Vector2 & vector)
{
	return Vector2(
		vector.x * mat_.getElement(0, 0) + vector.y * mat_.getElement(0, 1),
		vector.x * mat_.getElement(1, 0) + vector.y * mat_.getElement(1, 1)
	);
}

Matrix2D Matrix2D::createAngle(float angle)
{
	float sin = MathHelper::Sin(angle);
	float cos = MathHelper::Cos(angle);

	return Matrix2D(
		cos, -sin,
		sin, cos
	);
}

Vector2 operator*(const Vector2& vector, Matrix2D mat)
{
	return mat.transform(vector);
}
