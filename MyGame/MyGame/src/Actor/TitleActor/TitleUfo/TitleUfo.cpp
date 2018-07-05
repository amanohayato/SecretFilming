#include "TitleUfo.h"
#include <memory>

#include "../../../Graphic/Model.h"
#include "../../../Game/Time.h"
#include "../../../Math/MathHelper.h"

TitleUfo::TitleUfo(IWorld* world, const Vector3& start, const Vector3& goal) :
	Actor(world, "Ufo", start),
	startPos_(start),
	goalPos_(goal)
{
	initialize();
}

TitleUfo::~TitleUfo()
{
	
}

void TitleUfo::initialize()
{
	Vector3 temp = goalPos_ - startPos_;

	velocity_ = Vector3::Normalize(temp) * moveSpeed_;

	// ‰½ƒtƒŒ[ƒ€‚Å©g‚ğíœ‚·‚é‚©Œˆ‚ß‚é
	deleteTimer_ = (int)(Vector3::Distance(startPos_, goalPos_) / moveSpeed_);
}

void TitleUfo::update(float deltaTime)
{
	position_ += velocity_;

	deleteTimer_--;

	if (deleteTimer_ <= 0)
	{
		dead();
	}
}

void TitleUfo::draw() const
{
	Matrix mat = Matrix::Identity;
	mat = mat.Translation(position_);
	Model::GetInstance().Draw(MODEL_ID::MODEL_UFO, mat);
}