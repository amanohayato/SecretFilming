#pragma once
#include"../../../Math/Vector3.h"
#include"../../Model.h"


struct ParticlePieceParam {
	Vector3 position;
	Vector3 direction;
	float lifetime;
	MODEL_ID id;
	float size;
	float angle;
	float alpha;
	float speed;
	float swayrate;
};
class ParticlePiece {
public:
	ParticlePiece(const ParticlePieceParam& param);
	void update(float deltaTime);
	void draw()const;
	bool isDead()const;

	ParticlePieceParam getParam()const { return _param; }
private:
	ParticlePieceParam _param;
	bool _isDead{ false };
	int _sincount{ 0 };
	float _maxLife;
};