#pragma once
#include"Vector2.h"
#include"TwoDimensionalArray.h"

class Matrix2D {
public:
	Matrix2D();
	Matrix2D(float x1, float x2, float y1, float y2);
	~Matrix2D();
	Vector2 transform(const Vector2& vector);

	static Matrix2D createAngle(float angle);

private:
	TwoDimensionalArray<float> mat_;
};

Vector2 operator *(const Vector2& vector,Matrix2D mat);
