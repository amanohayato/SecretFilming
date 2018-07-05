#include "MissionStart.h"
#include "../../../Game/Time.h"
#include "../../../Math/MathHelper.h"

#include "../../../Graphic/Sprite.h"

#include "../../../Define.h"
MissionStart::MissionStart():
	Actor()
{
}

void MissionStart::initialize()
{
	mTime = 0.0f;
	mAlpha = 0.0f;

	mSize = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_MISSION_START);
	mSize /= 2.0f;
}

void MissionStart::update(float delta_time)
{
	mTime += Time::GetInstance().deltaTime();
	if (mTime <= 3.0f)
		mAlpha += Time::GetInstance().deltaTime();
	else
		mAlpha -= Time::GetInstance().deltaTime();

	mAlpha = MathHelper::Clamp(mAlpha, 0.0f, 1.0f);

	if (mTime > 0 && mAlpha == 0)dead();
}

void MissionStart::draw() const
{
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MISSION_START, Vector2((WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2))-mSize, mAlpha);
}
