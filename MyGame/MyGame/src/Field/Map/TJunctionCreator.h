#pragma once
#include"../Building/BuildingBase.h"
#include"../Field/FloorTilingMap.h"

#include<map>

class TJunctionCreator {
public:
	TJunctionCreator();

	void load(std::map<BuildingGroup, BuildingPtr>& buildingPairList, const std::string& buildingmap, const std::string& tilemap);
	void setFloor(MODEL_ID modelid);
	void draw(const Vector3& position, float angle, bool isUseTileMap=true)const;

private:
	std::list<BuildingPtr> buildings_;

	FloorTilingMap ftm_{};

	MODEL_ID _modelid{ MODEL_ID::MODEL_TJUNCTION_MAP };

};