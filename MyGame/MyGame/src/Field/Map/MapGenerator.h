#pragma once
#include "../Building/BuildingManager.h"
#include "../Building/BuildingBase.h"
#include<string>
#include<map>

#include "../../World/World.h"
#include"RandomEventCreator.h"
#include"TJunctionCreator.h"

class BuildingManager;
class BuildingCollisionMap;
class CsvReader;

 class MapGenerator {
public:
	MapGenerator(BuildingManager* buildingManager);

	void setUpList(IWorld* world);

	//��������t�@�C�����w�肷��
	void read(const std::string& filename);
	void read(const std::string& filename,const std::string& slicemap_filename);
	//�w�肳�ꂽ�t�@�C�������Ƀ}�b�v�𐶐�����
	void generate();
	//�t�@�C�����w�肵�A�����
	void generate(const std::string& filename);

	void setCollisionMap(const CsvReader& sliceReader,const BuildingPtr& building,int x, int z);

	void draw()const;

private:

	IWorld* world_;
	RandomEventCreator rec_{};
	const float cellSize_{16.5f};

	std::string filename_{};
	std::string slicemap_filename_{};

	std::map<BuildingGroup, BuildingPtr> buildingPairList_;

	BuildingManager* buildingManager_;
	std::weak_ptr<BuildingCollisionMap> collisionMap_;

	TJunctionCreator tjc_{};
	TJunctionCreator _outoffield_map{};

	std::function<void()> _createFunc;
 };
