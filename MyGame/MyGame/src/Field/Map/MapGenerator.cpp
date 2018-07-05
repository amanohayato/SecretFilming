#include "MapGenerator.h"
#include "../Building/Town/FishStore.h"
#include "../Building/Town/PoliceBox.h"
#include "../Building/Town/TakoyakiYatai.h"
#include "../Building/Town/House_1.h"
#include "../Building/Town/House_2.h"
#include "../Building/Town/Apartment_1.h"
#include "../Building/Town/Apartment_2.h"
#include "../Building/Town/SmokingArea.h"
#include "../Building/Town/VendingMachine.h"
#include "../Building/Town/EventBackStreetKaiwa.h"
#include "../Building/Town/EventBackStreetRati.h"
#include "../Building/Town/Neko/NekoBuilding.h"
#include "../Building/Town/Signal/Car_Signal.h"
#include "../Building/Town/Signal/Citizen_Signal1.h"
#include "../Building/Town/Signal/Citizen_Signal2.h"
#include"../../Resource/CsvReader.h"
#include"BuildingBlockSizeList.h"
#include"../../Scene/Manager/GameDataManager.h"

#include "../../Field/Building/Town/Manhoru/ManhoruBulding.h"
#include "../../Field/Building/Town/Kousaten/KousatenBulding.h"

#include<fstream>


MapGenerator::MapGenerator(BuildingManager* buildingManager) :
	buildingManager_(buildingManager),collisionMap_(buildingManager->getCollMap()){
	_createFunc = [&] {
		buildingPairList_[BuildingGroup::FISHSTORE] = std::make_shared<FishStore>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::POLICEBOX] = std::make_shared<PoliceBox>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::TAKOYAKISHOP] = std::make_shared<TakoyakiYatai>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::HOUSE_1] = std::make_shared<House_1>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::HOUSE_2] = std::make_shared<House_2>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::APARTMENT_1] = std::make_shared<Apartment_1>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::APARTMENT_2] = std::make_shared<Apartment_2>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::SMOKING_AREA] = std::make_shared<SmokingArea>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::VENDINGMACHINE_1] = std::make_shared<VendingMachine>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::BACKSTREET_RATI] = std::make_shared<EventBackStreetRati>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::BACKSTREET_KAIWA] = std::make_shared<EventBackStreetKaiwa>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::MANHORU] = std::make_shared<ManhoruBulding>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::KOUSATEN] = std::make_shared<KousatenBulding>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::NEKO] = std::make_shared<NekoBuilding>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::SIGNAL_ROADWAY] = std::make_shared<Car_Signal>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::SIGNAL_SIDEWALK1] = std::make_shared<Citizen_Signal1>(world_, Vector3::Zero, 0);
		buildingPairList_[BuildingGroup::SIGNAL_SIDEWALK2] = std::make_shared<Citizen_Signal2>(world_, Vector3::Zero, 0);

	};
}

void MapGenerator::setUpList(IWorld* world)
{
	world_ = world;

	//BuildingBlockSizeList blockSize{};
	//auto a = blockSize.getBlockSize(BuildingGroup::FISHSTORE);
	//auto b = blockSize.getBlockSize(BuildingGroup::POLICEBOX);
	//auto c = blockSize.getBlockSize(BuildingGroup::TAKOYAKISHOP);

	_createFunc();
	_createFunc = [] {};
}

void MapGenerator::read(const std::string & filename)
{
	filename_ = filename;
}

void MapGenerator::read(const std::string & filename, const std::string & slicemap_filename)
{
	read(filename);
	slicemap_filename_ = slicemap_filename;
}

void MapGenerator::generate()
{
	if (filename_.empty())return;
	CsvReader sliceReader;
	
	if (!slicemap_filename_.empty()) {
		sliceReader.load(slicemap_filename_);
		collisionMap_.lock()->initialize(sliceReader.columns()/ sliceSize+MathHelper::Sign(sliceReader.columns() % sliceSize), sliceReader.rows()/ sliceSize + MathHelper::Sign(sliceReader.rows() % sliceSize));
	}
	CsvReader reader{ filename_ };

	CsvReader texmap{ "res/Data/texturetypemap.csv" };

	float maxFieldSize = reader.rows()*cellSize_;
	std::vector<std::pair<int, char>> dataList_;

	//std::ofstream outputfile{ "waypoint.csv" };
	//int count = 0;

	rec_.initialize(Point(reader.columns() * (int)cellSize_ ,reader.rows() * (int)cellSize_ ));

	Vector2 mapSize;
	mapSize.x = cellSize_*reader.columns();
	mapSize.y = cellSize_*reader.rows();
	GameDataManager::getInstance().setMapSize(mapSize);

	for (int z = 0; z < reader.rows(); z++) {

		for (int x = 0; x < reader.columns(); x++) {

			auto data = reader.get(z, x);
			auto position = data.find("_");
			
			//ポイント情報を実際の座標に変換する用
			//if (data == "999") {
			//	outputfile << x*SQUARES_WIDTH + SQUARES_WIDTH*0.5f;
			//	outputfile << ",";
			//	outputfile << (reader.rows() - z)*SQUARES_HEIGHT - SQUARES_WIDTH*0.5f;
			//	outputfile << "\n";
			//}
			//continue;

			//座標情報に連番を付与する用
			//{
			//	outputfile << data;
			//	if (data == "6") {
			//		outputfile << "_";
			//		outputfile << count;
			//		count++;
			//	}
			//
			//	outputfile << ",";
			//
			//	continue;
			//}
			if (std::string::npos == position)
			{
				continue;
			}

			int type = atoi(data.substr(0, position).c_str());

			if (type == 0)continue;

			char dirC = data.substr(++position).front();
			int dir = atoi(&dirC);
			//dataList_.push_back(std::make_pair(type, dir));

			BuildingPtr tempPtr = buildingPairList_[static_cast<BuildingGroup>(type)]->clone(world_, x, reader.rows() - z, dir);
			
			auto textype = texmap.get(z, x);
			if (textype.find("Tex") != textype.npos) {
				auto texpos = textype.find("_");
				int texnum = atoi(textype.substr(++position).c_str());
				tempPtr->setTexture(texnum);
			}

			MV1SetupCollInfo(tempPtr->getModelHandle(), -1, 8, 8, 8);

			buildingManager_->add(tempPtr);
			int a = reader.rows() - (z+1);
			if (tempPtr->getEvent() != EventType::EVENT_BACKSTREET_KAIWA&&
				tempPtr->getEvent() != EventType::EVENT_BACKSTREET_RATI&&
				tempPtr->getEvent() != EventType::EVENT_JUNCTION&&
				tempPtr->getEvent() != EventType::EVENT_NEKO) {
				setCollisionMap(sliceReader, tempPtr, x, z/*reader.rows() - (z+1)*/);
			}
			//イベント持ちのみイベントリストに追加
			if (tempPtr->getEvent() != EventType::EVENT_NULL) {
				rec_.add(tempPtr->getPosition(), tempPtr);
			}

		}
		//outputfile << "\n";

	}

	rec_.chooseEvent(world_);

	tjc_.load(buildingPairList_, "res/Data/tjunctionmap.csv", "res/Data/tjunctiontilemap.csv");
	tjc_.setFloor(MODEL_ID::MODEL_TJUNCTION_MAP);
	_outoffield_map.load(buildingPairList_, "res/Data/outoffieldmap.csv", "res/Data/outoffieldtilemap.csv");
	_outoffield_map.setFloor(MODEL_ID::MODEL_OUTOFFIELD);

}

void MapGenerator::generate(const std::string & filename)
{
	read(filename);
	generate();
}


void MapGenerator::setCollisionMap(const CsvReader& sliceReader, const BuildingPtr& building, int x, int z)
{
	if (sliceReader.rows() == 0)return;

	auto colList = sliceReader.get(z, x);

	int cellx, cellz;
	while (!colList.empty()) {
		auto cellPos = colList.find(" ");
		if (cellPos == std::string::npos)break;

		auto cellVec = colList.substr(0, cellPos);
		auto xzSlicePos = cellVec.find("_");
		auto n = cellVec.substr(0, xzSlicePos);
		cellx = atoi(cellVec.substr(0, xzSlicePos).c_str());
		cellz = atoi(cellVec.substr(++xzSlicePos).c_str());

		collisionMap_.lock()->add(building, cellx, cellz);

		colList=colList.substr(++cellPos, colList.size());
	}

}

void MapGenerator::draw() const
{
	tjc_.draw(Vector3{ 478.5f,0.0f,0.0f }, 180.0f);
	tjc_.draw(Vector3{ 973.5f,0.0f,1254.0f }, 0.0f);
	tjc_.draw(Vector3{ 1468.5f,0.0f,0.0f }, 180.0f);
	_outoffield_map.draw(Vector3{ 528.0f,0.0f,1254.0f }, 0.0f, false);
	_outoffield_map.draw(Vector3{ 742.5f,0.0f,0.0f }, 180.0f, false);
	_outoffield_map.draw(Vector3{ 957.0f,0.0f,0.0f }, 180.0f, false);
	_outoffield_map.draw(Vector3{ 0.0f,0.0f,197.5f }, 270.0f, false);
	_outoffield_map.draw(Vector3{ 0.0f,0.0f,693.0f }, 270.0f, false);
	_outoffield_map.draw(Vector3{ 1468.5f,0.0f,1254.0f }, 90.0f, false);
	_outoffield_map.draw(Vector3{ 1468.5f,0.0f,297.0f }, 90.0f, false);
	_outoffield_map.draw(Vector3{ 1468.5f,0.0f,775.5f }, 90.0f, false);
	_outoffield_map.draw(Vector3{ 115.5f,0.0f,1254.0f }, 0.0f, false);

}
	

