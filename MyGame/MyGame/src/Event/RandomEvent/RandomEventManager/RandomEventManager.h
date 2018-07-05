#pragma once
#include "../../../Resource/CsvReader.h"
#include "../../../World/IWorld.h"
#include "../RandomEvent/RandomEventBase/IRandomEventPtr.h"
#include "../RandomEventProbability/RandomEventProbability.h"
#include <unordered_map>

enum class RandomEvent;
enum class RandomEventArea;

class RandomEventManager
{
public:
	// �R���X�g���N�^
	RandomEventManager(IWorld& world);
	// �ǂݍ���
	void Load();
	// ������  
	void Initialize();
	// �X�V
	void Update();
	// �`��  
	void Draw() const;
	// �f�o�b�O����
	void DebugDraw();
	// �I��    
	void End();
	// �����_���C�x���g�̒ǉ� 
	void Add(RandomEvent name, const IRandomEventPtr& event);
	// �����_���C�x���g�̕ύX   
	void Change(RandomEvent name);
	void SetPosition(const Vector3& position);
	// �R�s�[�֎~    
	RandomEventManager(const RandomEventManager& other) = delete;
	RandomEventManager& operator = (const RandomEventManager& other) = delete;

private:
	// ���W���}�X�ڂɕϊ�����
	Vector2 ToSquares(const Vector3& pos);
	// �ǂ̃G���A�ɂ��邩�𔻒�
	RandomEventArea CheckArea(const Vector2& pos);
	// �G���A�̊m����ݒ�
	void SetUp(const RandomEventArea& area);
	// �����m���𔻒肷��
	void Judgment();

private:
	// �����_���C�x���g
	std::unordered_map<RandomEvent, IRandomEventPtr> randomEvents_;
	// ���݂̏��
	std::weak_ptr<IRandomEvent> currentRandomEvent_;
	// CSV�ǂݍ���
	CsvReader csvReader_;
	// �G���A�̊m����ݒ肵�Ă������
	RandomEventProbability eventProbability_;
	// �G���A�̊m��
	std::vector<float> probability_;
	// ���݂̃G���A
	RandomEventArea currentArea_;
	// 1�t���[���O�̃G���A
	RandomEventArea prevArea_;
	// ���[���h
	IWorld* world_;
	// ���݂̃}�X��
	Vector2 currentSquares_;
	// 1�t���[���O�̃}�X��
	Vector2 prevSquares_;
};