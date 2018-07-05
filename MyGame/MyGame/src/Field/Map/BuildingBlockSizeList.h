#pragma once
#include"../../Resource/CsvReader.h"
#include"../../Math/Point.h"
#include"../../ID/EnumIDs.h"

class BuildingBlockSizeList {
public:
	BuildingBlockSizeList();
	Point getBlockSize(BuildingGroup type);
private:
	CsvReader list_;
};