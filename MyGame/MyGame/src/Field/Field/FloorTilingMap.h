#pragma once
#include<vector>

#include"../../Resource/CsvReader.h"

class FloorTilingMap {
public:
	FloorTilingMap() {

	}
	void initialize() {
		initialize("res/Data/tilemap.csv");
	}
	void initialize(const std::string& filepath) {
		CsvReader cr(filepath);
		auto i = cr.rows();
		auto i2 = cr.columns();
		for (int y = 0; y < cr.rows(); y++) {
			for (int x = 0; x < cr.columns(); x++) {
				int target = cr.geti(y, x);
				tilingMap_.push_back(target);
			}
		}

		width_ = i2;
		height_ = i;

	}
	//1ŽŸŒ³ƒQƒbƒg
	int get(int i) const{
		return(i >= tilingMap_.size()) ? tilingMap_[tilingMap_.size() - 1] : tilingMap_[i];
	}
	//2ŽŸŒ³ƒQƒbƒg
	int get(int x, int y)const {
		return tilingMap_[x + y*width_];
	}

	int getWidth()const { return width_; }
	int getHeight()const { return height_; }

private:
	std::vector<int> tilingMap_;

	int width_;
	int height_;

};