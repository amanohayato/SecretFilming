#ifndef BUILDING_MANAGER_H_
#define BUILDING_MANAGER_H_

#include "BuildingBase.h"
#include"BuildingCollisionMap.h"
#include"BuildingPtr.h"

#include<list>

class BuildingManager {
public:
	BuildingManager();

	// ������
	void initialize();
	// �X�V
	void update(float deltaTime);
	// �`��
	void draw() const;
	// �폜
	void remove();
	// �����̒ǉ�
	void add(const BuildingPtr& actor);
	// �ǉ�
	void clone(int buildingNum, IWorld* world, const Vector3& position, int rotationNum);
	// ������Ԃ�
	unsigned int count() const;

	std::list<BuildingPtr>& get();
	std::weak_ptr<BuildingCollisionMap> getCollMap()const;
	void collide();

	// ����
	void clear();

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);

	// �R�s�[�֎~
	BuildingManager(const BuildingManager& other) = delete;
	BuildingManager& operator = (const BuildingManager& other) = delete;

	using BuildingList = std::list<BuildingPtr>;
	// �A�N�^�[���X�g
	BuildingList	buildings_;

	std::shared_ptr<BuildingCollisionMap> collisionMap_{};
};

#endif // !BUILDING_MANAGER_H_

