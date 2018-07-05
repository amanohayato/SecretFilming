#pragma once
#include"../../../Math/Vector3.h"
#include"ParticlePiece.h"

#include<list>

struct ParticleCreateParam {
	Vector3 create_position;
	float lifetime;
	float create_interval;
	float dir_random_angle;
	float lifetime_random_range;
	float speed_random_range;
	ParticlePieceParam param;
};

class ParticleManager {
public:
	ParticleManager();
	void initalize(ParticleCreateParam pp);
	void update(float deltaTime);
	void draw()const;

	bool isDead()const;
private:
	ParticleCreateParam _param;

	bool _isDead{ false };

	float CREATE_INTERVAL;

	std::list<std::shared_ptr<ParticlePiece>> _particles;
};