#include "Police.h"
#include "../../../World/World.h"

#include "../../../Graphic/Model.h"
#include "../../Enemy/EnemyBase.h"
#include "../../EventActor/EventUtility/MoveActor.h"
Police::Police(IWorld * world, const Matrix& mat) :
	Actor(world, "Police", mat.Translation()),
	mAnim(Model::GetInstance().GetHandle(MODEL_ID::MODEL_POLICE))
{
	mPoliceMat = mat;
	mStartMat = mat;
}

void Police::initialize()
{
	mAnim.changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_POLICE, (int)PoliceAnim::POLICE_IDLE_ANIM), true);

}

void Police::update(float deltaTime) {
	mAnim.update(0.8f);
}

void Police::draw() const
{
	//‚È‚ñ‚©’n–Ê‚ÌˆÊ’u‚ª‚¨‚©‚µ‚¢‚©‚à
	mAnim.Draw(Matrix::CreateFromAxisAngle(Vector3::Up, 180.0f)*mPoliceMat);
}

void Police::shadowDraw() const
{
	draw();
}

AnimationOutSide & Police::GetAnimation()
{
	return mAnim;
}

Matrix & Police::GetMatrix()
{
	return mPoliceMat;
}

Matrix Police::GetStartMat()
{
	return mStartMat;
}
