#include "RandomEventProbability.h"
#include "../RandomEventArea.h"
#include <DxLib.h>

// �R���X�g���N�^
RandomEventProbability::RandomEventProbability() {
}

// �ǂݍ���
void RandomEventProbability::Load()
{
	csvReader_.load("res/Data/eventProbability.csv");
}

// �n���ꂽ�G���A�̔����m����Ԃ�
std::vector<float> RandomEventProbability::SetUp(const RandomEventArea & area)
{
	currentArea_ = area;
	increase_ += 0.1f;
	auto col = csvReader_.columns();

	for (int i = 0; i < col; i++) {
		auto num = csvReader_.geti(static_cast<int>(area), i);
		probability_.at(i) = (float)num;
		// �����G���A�ɂ����甭���m���𑝉�������
		if (static_cast<int>(area) != 0) {
			probability_.at(i) *= increase_;//��Z�ɂ����Ⴂ�܂����A��肠��΍ďC�����肢���܂�
		}
	}
	return probability_;
}

// �����m���𔻒肷��
RandomEvent RandomEventProbability::Judgment()
{
	for (int i = 0; i < probability_.size(); i++) {
		if (probability_[i] >= (std::rand() % 100) + 1) {
			// ��������0%�ɖ߂�
			increase_ = 0.0f;
			// �m�����Đݒ�
			SetUp(currentArea_);
			// ��������C�x���g��Ԃ�
			return static_cast<RandomEvent>(i + 1);
		}
	}
	return RandomEvent::Null_Eve;
}
