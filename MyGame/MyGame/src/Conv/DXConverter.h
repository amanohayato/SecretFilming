#pragma once
#include "DxLib.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Color.h"
#include "../Math/Matrix.h"

class DXConverter
{
private:
	DXConverter() = default;
	~DXConverter() = default;

public:
	static DXConverter &GetInstance()
	{
		static DXConverter d;
		return d;
	}

	// Vector3→VECTORに変換して返す
	VECTOR ToVECTOR(const Vector3& v) const;
	// VECTOR→Vector3に変換して返す
	Vector3 ToVector3(const VECTOR& v) const;

	// Vector3→Colorに変換して返す
	int ToColor(const Vector3& v) const;

	// Matrix→MATRIXに変換して返す
	MATRIX ToMATRIX(const Matrix& m) const;
	// MATRIX→Matrixに変換して返す
	Matrix ToMatrix(const MATRIX& m) const;
};