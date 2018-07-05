#pragma once
#include "../../Math/Collision/CollisionMesh.h"
#include "../../ID/EnumIDs.h"
#include "../../Field/FieldOut.h"

class Skybox {
public:
	Skybox(int skybox = -1);
	void update(float deltaTime);
	void draw() const;
	CollisionMesh& getOutMesh();

	Skybox(const Skybox& other) = delete;
	Skybox& operator = (const Skybox& other) = delete;

private:
	int skybox_;
	FieldOut out_;
};