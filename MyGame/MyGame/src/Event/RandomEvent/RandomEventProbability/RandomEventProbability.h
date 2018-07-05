#pragma once
#include "../../../Resource/CsvReader.h"
#include "../RandomEvent/RandomEventBase/RandomEvent.h"

enum class RandomEventArea;

class RandomEventProbability
{
public:
	// �R���X�g���N�^
	RandomEventProbability();
	// �ǂݍ���
	void Load();
	// �n���ꂽ�G���A�̔����m����Ԃ�
	std::vector<float> SetUp(const RandomEventArea& area);
	// �����m���𔻒肷��
	RandomEvent Judgment();

private:
	// CSV�ǂݍ���
	CsvReader csvReader_;
	// �G���A���Ƃ̊m��
	std::vector<float> probability_{ std::vector<float>(2) };
	// ���݂̃G���A
	RandomEventArea currentArea_;
	// ������
	float increase_{ 0.0f };
};
