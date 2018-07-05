#include "ParticlePiece.h"
#include"../../../Math/MathHelper.h"

ParticlePiece::ParticlePiece(const ParticlePieceParam & param):_param(param),_maxLife(_param.lifetime)
{
}

void ParticlePiece::update(float deltaTime)
{
	_param.lifetime -= deltaTime;
	if (_param.lifetime <= 0.0f) {
		_isDead = true;
		return;
	}

	_param.position += _param.direction*_param.speed;

	_sincount+=10;

}

void ParticlePiece::draw() const
{
	Vector2 origin;
	origin.x = 0.5f;
	origin.y = 0.5f;
	auto drawpos = _param.position;
	auto left = _param.direction;
	left.y = _param.direction.x;
	left.x = _param.direction.y;
	float sin = MathHelper::Sin((float)_sincount);
	drawpos += left *sin*0.1f;
	auto alpha = MathHelper::Lerp(1.0f, 0.0f, (_maxLife - _param.lifetime) / _maxLife)*_param.alpha;
	Model::GetInstance().Draw2D(_param.id, drawpos, 0, _param.size, origin, _param.angle, _param.alpha, TRUE, FALSE);
}


bool ParticlePiece::isDead() const
{
	return _isDead;
}
