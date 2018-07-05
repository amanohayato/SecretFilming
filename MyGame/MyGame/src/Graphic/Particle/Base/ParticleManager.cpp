#include "ParticleManager.h"
#include"../../../Math/Random.h"

ParticleManager::ParticleManager()
{

}

void ParticleManager::initalize(ParticleCreateParam pp)
{
	_isDead = false;
	_particles.clear();
	_param = pp;
	_param.param.position = _param.create_position;

	CREATE_INTERVAL = _param.create_interval;
}

void ParticleManager::update(float deltaTime)
{
	for (auto& pp : _particles) {
		pp->update(deltaTime);
	}
	_particles.remove_if([](std::shared_ptr<ParticlePiece>& pp) {return pp->isDead(); });

	_param.lifetime -= deltaTime;
	if (_param.lifetime <= 0.0f) {
		_isDead = true;
		return;
	}
	_param.create_interval -= deltaTime;
	if (_param.create_interval <= 0.0f) {
		_param.create_interval = CREATE_INTERVAL;
		ParticlePieceParam param = _param.param;
		Matrix mat(Matrix::Identity);
		mat = mat.Up(_param.param.direction).NormalizeRotationMatrix_BaseUp();
		mat *= Matrix::CreateFromAxisAngle(mat.Left(), Random::GetInstance().Range(-_param.dir_random_angle, _param.dir_random_angle));
		mat *= Matrix::CreateFromAxisAngle(mat.Forward(), Random::GetInstance().Range(-_param.dir_random_angle, _param.dir_random_angle));
		param.direction = mat.Up();
		param.lifetime += Random::GetInstance().Range(-_param.lifetime_random_range, _param.lifetime_random_range);
		param.speed += Random::GetInstance().Range(-_param.speed_random_range, _param.speed_random_range);
		_particles.push_back(std::make_shared<ParticlePiece>(param));
	}

	Vector3 camPos = GetCameraPosition();
	Vector2 camPos2d{ camPos.x,camPos.z };
	//_particles.sort([&](auto& p1, auto& p2) { 
	//	return Vector2::Distance(camPos2d, Vector2{ p1->getParam().position.x,p1->getParam().position.z }) > Vector2::Distance(camPos2d, Vector2{ p2->getParam().position.x,p2->getParam().position.z });
	//});
}

void ParticleManager::draw() const
{
	for (auto& pp : _particles) {
		pp->draw();
	}
}

bool ParticleManager::isDead() const
{
	return (_particles.empty());
}
