#include "TitleUfoFactory.h"
#include "TitleUfo.h"
#include "../../../Math/Random.h"

TitleUfoFactory::TitleUfoFactory(IWorld * world):
	Actor(world, "", Vector3::Zero)
{
}

void TitleUfoFactory::initialize()
{
	spawnCounter_ = spawnInterval_;
}

void TitleUfoFactory::update(float deltaTime)
{
	// カウンターのカウントアップ
	spawnCounter_++;

	// カウントが規定値に達したら
	if (spawnCounter_ >= spawnInterval_)
	{
		Vector3 ufoVelocity = Vector3(Random::GetInstance().Range(-1.0f, 1.0f), 0, Random::GetInstance().Range(-1.0f, 1.0f));

		ufoVelocity *= 2000;

		Vector3 startPos = centerPos_ +  ufoVelocity;

		Vector3 endPos = centerPos_ - ufoVelocity;

		std::shared_ptr<TitleUfo> ufo = std::make_shared<TitleUfo>(world_, startPos, endPos);

		addChild(ufo);

		spawnCounter_ = 0;
	}
}

void TitleUfoFactory::draw() const
{
}
