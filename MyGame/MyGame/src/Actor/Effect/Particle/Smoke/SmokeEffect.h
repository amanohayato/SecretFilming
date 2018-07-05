#pragma once
#include"../../../../Graphic/Particle/Base/ParticleManager.h"
#include"../../../Actor.h"

class SmokeEffect:public Actor {
public:
	SmokeEffect(const Vector3& position);
	void initialize();

	void update(float deltaTime);

	void draw()const;

private:
	ParticleManager _particle;
};