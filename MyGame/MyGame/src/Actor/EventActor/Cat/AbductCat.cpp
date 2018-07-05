#include "AbductCat.h"
#include"../../../Graphic/Model.h"
#include"../../../Sound/Sound.h"

AbductCat::AbductCat(IWorld * world, const Vector3 & position):
	Actor(world, "EventCar", position)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_CAT));
	animation_.ChangeAnim(0);
	updatefunc_ = [] {};
	playSEfunc_ = [] {};
}

void AbductCat::initialize()
{
}

void AbductCat::update(float deltaTime)
{
	updatefunc_();

	
}

void AbductCat::draw() const
{
	animation_.Draw(getPose());
}

void AbductCat::receiveMessage(EventMessage em, void * param)
{
	if (em != EventMessage::Abduct_Cat)return;

	playSEfunc_ = [&] {
		if (!Sound::GetInstance().IsPlaySE(SE_ID::NEKO_VOICE_SE)) {
			Sound::GetInstance().Play3DSE(SE_ID::NEKO_VOICE_SE, (VECTOR*)&position_);
		}
	};
	updatefunc_ = [&] {
		if (animation_.GetCurrentAnimFrame() >= 40.0f) {
			playSEfunc_();
			playSEfunc_ = [] {};
		}
		animation_.Update(0.5f);
	};
}

void AbductCat::dead()
{
	Sound::GetInstance().StopSE(SE_ID::NEKO_VOICE_SE);

	Actor::dead();
}
