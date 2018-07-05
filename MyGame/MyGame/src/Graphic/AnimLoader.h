#pragma once
#include<vector>
#include<list>
#include<map>
#include<DxLib.h>
#include"../ID/EnumIDs.h"


//アニメーションを別ファイルに持つモデル用のアニメーション読み込みクラス
class AnimLoader {
private:
	AnimLoader() = default;
	~AnimLoader() {
		anims_.clear();
	};

public:
	static AnimLoader& getInstance() {
		static AnimLoader load;
		return load;
	}

	//アニメーションのセット
	int loadAnim(MODEL_ID model,const std::string& anim) {
		int key = MV1LoadModel(anim.c_str());
		anims_.at(model).push_back(key);
		return (int)anims_.size() - 1;
	}
	//アニメーションの一括セット
	void loadAnims(MODEL_ID model, const std::list<std::string> anims) {
		for (auto i : anims) {
			int key = MV1LoadModel(i.c_str());
			anims_[model].push_back(key);
		}
	}
	//アニメーションキーの取得
	int getAnimKey(MODEL_ID model, int key) const{
		return anims_.at(model)[key];
	}


private:
	std::map<MODEL_ID,std::vector<int>> anims_;
};