#include "MoveActor.h"
#include "../../../Game/Time.h"

#include "../../../Math/MathHelper.h"

#include "../../../Graphic/DebugDraw.h"
#include "../../../Math/Vector2.h"
MoveActor::MoveActor()
{
}

MoveActor::~MoveActor()
{
}

bool MoveActor::Move(Matrix & mat, Matrix  goal)
{
	//スタートからゴールまでのベクトルを求める
	Vector3 vec = (goal.Translation() - mat.Translation());
	vec.y = 0.0f;

	//スタートとエンドのベクトルを返す
	Matrix s;
	s.Forward(vec);
	s.Up(Vector3::Up);
	s.Right(Vector3::Cross(vec, Vector3::Up));
	float vecAngle = Matrix::Angle(s).y;

	//回転要素
	auto a = Matrix::Angle(mat).y;
	auto b = Matrix::Angle(goal).y;



	//目的地だったら
	if (vec.Length() <= 1.0f) {

		//最後の回転
		if (MathHelper::Abs(a - b) >= 5.0f) {
			float angle = 1.0f;
			Matrix derMat = mat;
			derMat *= Matrix::CreateTranslation(goal.Forward());
			if (Direction(mat,derMat) > 0.0f)angle = -1;
			//原点に戻して回転させて元の位置に戻す
			mat *=
				Matrix::CreateTranslation(-mat.Translation())*
				Matrix::CreateRotationY(5.0f*angle)*
				Matrix::CreateTranslation(mat.Translation());
			return false;
		}
		else
		{
			//全ての補間が終了
			return true;
		}
		return false;
	}
	else if (MathHelper::Abs(a - vecAngle) >= 5.0f) {
		float angle = 1.0f;
		if (Direction(mat,goal) > 0.0f)angle = -1.0f;
		//原点に戻して回転させて元の位置に戻す
		mat *=
			Matrix::CreateTranslation(-mat.Translation())*
			Matrix::CreateRotationY(5.0f*angle)*
			Matrix::CreateTranslation(mat.Translation());
		return false;
	}
	//最初の回転




	//正規化
	vec = vec.Normalize();
	//座標移動
	mat *=
		Matrix::CreateTranslation(vec);


	//DebugDraw::DebugDrawLine3D(Vector3::VECTORToVector3(mat.Translation()), Vector3::VECTORToVector3(mat.Translation() + (vec*20.0f)), GetColor(255, 0, 0));

	return false;
}

float MoveActor::Direction(Matrix& mat1, Matrix& mat2)
{
	Vector2 v1 = Vector2(mat1.Right().x, mat1.Right().z);
	v1.Normalize();
	Vector3 vec = mat2.Translation() - mat1.Translation();
	Vector2 v2 = Vector2(vec.x, vec.z);
	v2.Normalize();
	return Vector2::Dot(v1, v2);
}
