#pragma once
#include<vector>
#include<list>
#include<map>
#include<DxLib.h>
#include"../ID/EnumIDs.h"


//�A�j���[�V������ʃt�@�C���Ɏ����f���p�̃A�j���[�V�����ǂݍ��݃N���X
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

	//�A�j���[�V�����̃Z�b�g
	int loadAnim(MODEL_ID model,const std::string& anim) {
		int key = MV1LoadModel(anim.c_str());
		anims_.at(model).push_back(key);
		return (int)anims_.size() - 1;
	}
	//�A�j���[�V�����̈ꊇ�Z�b�g
	void loadAnims(MODEL_ID model, const std::list<std::string> anims) {
		for (auto i : anims) {
			int key = MV1LoadModel(i.c_str());
			anims_[model].push_back(key);
		}
	}
	//�A�j���[�V�����L�[�̎擾
	int getAnimKey(MODEL_ID model, int key) const{
		return anims_.at(model)[key];
	}


private:
	std::map<MODEL_ID,std::vector<int>> anims_;
};