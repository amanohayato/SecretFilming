#ifndef BUILDING_MANAGER_H_
#define BUILDING_MANAGER_H_

#include "BuildingBase.h"
#include"BuildingCollisionMap.h"
#include"BuildingPtr.h"

#include<list>

class BuildingManager {
public:
	BuildingManager();

	// 初期化
	void initialize();
	// 更新
	void update(float deltaTime);
	// 描画
	void draw() const;
	// 削除
	void remove();
	// 建物の追加
	void add(const BuildingPtr& actor);
	// 追加
	void clone(int buildingNum, IWorld* world, const Vector3& position, int rotationNum);
	// 総数を返す
	unsigned int count() const;

	std::list<BuildingPtr>& get();
	std::weak_ptr<BuildingCollisionMap> getCollMap()const;
	void collide();

	// 消去
	void clear();

	bool hitToLine(Vector3 firstPos, Vector3 secondPos);

	// コピー禁止
	BuildingManager(const BuildingManager& other) = delete;
	BuildingManager& operator = (const BuildingManager& other) = delete;

	using BuildingList = std::list<BuildingPtr>;
	// アクターリスト
	BuildingList	buildings_;

	std::shared_ptr<BuildingCollisionMap> collisionMap_{};
};

#endif // !BUILDING_MANAGER_H_

