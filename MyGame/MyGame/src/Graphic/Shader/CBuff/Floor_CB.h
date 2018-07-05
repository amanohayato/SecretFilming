#pragma once
#include"../CBuff_Struct.h"

static constexpr int CELLTYPE_SIZE = 1672;
struct Floor_CB {

	float gridSize;
	float maxXSize;
	float maxYSize;
	int columnSize;
	cbuff_struct::int4 celltype[CELLTYPE_SIZE];

};
