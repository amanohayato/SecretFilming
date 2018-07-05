#pragma once
#include "../../../Math/Matrix.h"

#include "../../../Math/Vector3.h"
class MoveActor {
public:
	MoveActor();
	~MoveActor();


	//終わっていたらtrueを返す
	static bool Move(Matrix& mat, Matrix goal);

private:
	static float Direction(Matrix& mat1, Matrix& mat2);
private:
	bool mIsEndMove;
};