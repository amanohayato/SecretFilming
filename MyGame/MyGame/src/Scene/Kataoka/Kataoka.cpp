#include "Kataoka.h"

#include "../../Event/EventManager/EventManager.h"

#include "../../Input/Keyboard.h"

#include "../../Game/Time.h"

#include "../../Graphic/Model.h"

#include "../../Camera/Camera.h"

#include "../../Actor/EventActor/EventUtility/MoveActor.h"

Kataoka::Kataoka():
	mWorld()
{

}

void Kataoka::start()
{
	isEnd_ = false;
	//next_ = SceneType::SCENE_MAINMENU;



	mPos = Vector2::Zero;
	
	
	mVMat = 
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(20.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(Vector3::Zero);
	mMat = Matrix::Identity;

	mLerpTime = 0.0f;
	mLerpMat = Matrix::Identity;
}

void Kataoka::update(float deltaTime)
{
	Vector2 line1 = Vector2(20, 20);
	Vector2 line2 = Vector2(45, 20);

	int color = GetColor(255, 255, 255);


	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) {
		mPos.y += 20.0f*Time::GetInstance().deltaTime();
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)){
		mPos.x -= 20.0f*Time::GetInstance().deltaTime();
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) {
		mPos.y -= 20.0f*Time::GetInstance().deltaTime();

	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) {
		mPos.x += 20.0f*Time::GetInstance().deltaTime();
	}


	mVMat =
		Matrix::CreateScale(Vector3::One)*
		Matrix::CreateRotationX(0.0f)*
		Matrix::CreateRotationY(20.0f)*
		Matrix::CreateRotationZ(0.0f)*
		Matrix::CreateTranslation(Vector3(mPos.x, 0, mPos.y));



	//DebugDraw::DebugDrawCircle(mPos.x, mPos.y, 30.0f, color);
	//DebugDraw::DebugDrawLine(line1.x, line1.y, line2.x, line2.y, color);

	DebugDraw::DebugDrawFormatString(32, 32, GetColor(255, 255, 255), std::to_string(Direction(mMat, mVMat)));
	//Matrix mat1 =
	//	Matrix::CreateScale(Vector3::One)*
	//	Matrix::CreateRotationX(0.0f)*
	//	Matrix::CreateRotationY(0.0f)*
	//	Matrix::CreateRotationZ(0.0f)*
	//	Matrix::CreateTranslation(mPos);

	Camera::GetInstance().SetRange(0.5f, 1000.0f);
	Camera::GetInstance().Position.Set(Vector3(100, 100, 100));
	Camera::GetInstance().Target.Set(Vector3::Zero);
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().Update();

}

void Kataoka::draw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_CAR_BLUE, mMat);
	Model::GetInstance().Draw(MODEL_ID::MODEL_CAR_GRAY, mVMat);
}

void Kataoka::end()
{
}

float Kataoka::Direction(const Matrix& mat1, const Matrix& mat2)
{

	
	Vector2 v1 = Vector2(mat1.Right().x, mat1.Right().z);
	v1.Normalize();
	Vector3 vec = mat2.Translation() - mat1.Translation();
	Vector2 v2 = Vector2(vec.x, vec.z);
	v2.Normalize();

	return Vector2::Dot(v1, v2);


	//Vector2 v = line2 - line1;
	//Vector2 c = pos - line1;

	//float n1 = Vector2::Dot(v, c);

	//if (n1 < 0) {
	//	return (Vector2::Distance(line1, pos) < radius) ? true : false;
	//}

	//float n2 = Vector2::Dot(v, v);
	//if (n1 > n2) {
	//	float len = MathHelper::Pow(Vector2::Distance(line2, pos), 2.0f);
	//	return (len < MathHelper::Pow(radius, 2.0f)) ? true : false;
	//}
	//else
	//{
	//	float n3 = Vector2::Dot(c, c);
	//	return (n3 - (n1 / n2)*n1 < MathHelper::Pow(radius, 2.0f)) ? true : false;
	//}
}
