#pragma once
#include "../../Math/Collision/CollisionMesh.h"
#include "../../ID/EnumIDs.h"
#include"FloorTilingMap.h"
//#include "../../../Field/FieldOut.h"
#include"../../Math/TwoDimensionalArray.h"

// �t�B�[���h�i�I�����[�j�N���X
class Field {
public:
	// �R���X�g���N�^
	Field(int field = -1);
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	void shadowDraw()const;
	// �t�B�[���h�̃n���h���擾
	int modelHandle(); // Probably no longer needed?
	CollisionMesh& getMesh();
	// �R�s�[�֎~
	Field(const Field& other) = delete;
	Field& operator = (const Field& other) = delete;

	int getFloorTile(int x,int y) const;

	int getWidth()const;
	int getHeight()const;
private:
	int field_;
	CollisionMesh mesh_;

	FloorTilingMap ftm_{};

};