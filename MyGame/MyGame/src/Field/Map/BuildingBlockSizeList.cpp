#include "BuildingBlockSizeList.h"

BuildingBlockSizeList::BuildingBlockSizeList() :list_{"res/Data/building_block_size.csv"}
{
}

Point BuildingBlockSizeList::getBlockSize(BuildingGroup type)
{
	return Point(list_.geti((int)type, 0), list_.geti((int)type, 1));
}
