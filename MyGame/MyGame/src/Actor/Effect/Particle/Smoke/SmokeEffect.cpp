#include "SmokeEffect.h"

SmokeEffect::SmokeEffect(const Vector3& position):_particle(),
	Actor(nullptr,"Smoke",position)
{
}

void SmokeEffect::initialize()
{
	ParticleCreateParam param;
	param.create_interval = 0.0001f;
	param.create_position=position_;
	param.lifetime_random_range = 0.2f;
	param.speed_random_range = 0.02f;
	param.dir_random_angle = 5.0f;
	param.lifetime = 5.0f;
	param.param.alpha = 0.3f;
	param.param.angle = 0.0f;
	param.param.direction = Vector3::Up;
	param.param.id = MODEL_ID::SPRITE_SMOKE;
	param.param.lifetime = 5.0f;
	param.param.size = 0.6f;
	param.param.speed = 0.05f;
	_particle.initalize(param);
}

void SmokeEffect::update(float deltaTime)
{
	_particle.update(deltaTime);
	if (_particle.isDead())dead();
}

void SmokeEffect::draw() const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	_particle.draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
