#include "RandomEventManager.h"
#include "../RandomEventProbability/RandomEventProbability.h"
#include "../RandomEvent/NullRandomEvent/NullRandomEvent.h"
#include "../RandomEvent/SignalRandomEvent/SignalRandomEvent.h"
#include "../RandomEvent/FallDownRandomEvent/FallDownRandomEvent.h"
#include "../RandomEvent/RandomEventBase/RandomEvent.h"
#include "../RandomEventArea.h"
#include "../../../Actor/Enemy/EnemyBase.h"
#include "../../../World/World.h"
#include <assert.h>
#include <DxLib.h>

// �R���X�g���N�^
RandomEventManager::RandomEventManager(IWorld& world)
	: world_(&world), currentRandomEvent_() {
	Load();
	Add(RandomEvent::Null_Eve, std::make_shared<NullRandomEvent>(world));
	Add(RandomEvent::FallDown_Eve, std::make_shared<FallDownRandomEvent>(world));
	Add(RandomEvent::Signal_Eve, std::make_shared<SignalRandomEvent>(world));
	Change(RandomEvent::Null_Eve);
	currentRandomEvent_.lock()->Initialize();
}

// �ǂݍ���
void RandomEventManager::Load()
{
	csvReader_.load("res/Data/randomEvent.csv");
	eventProbability_.Load();
}

// ������
void RandomEventManager::Initialize()
{
	End();
	randomEvents_.clear();
	Add(RandomEvent::Null_Eve, std::make_shared<NullRandomEvent>(*world_));
	Add(RandomEvent::FallDown_Eve, std::make_shared<FallDownRandomEvent>(*world_));
	Add(RandomEvent::Signal_Eve, std::make_shared<SignalRandomEvent>(*world_));
	Change(RandomEvent::Null_Eve);
	currentRandomEvent_.lock()->Initialize();
}

// �X�V
void RandomEventManager::Update()
{
	prevSquares_ = currentSquares_;
	currentSquares_ = ToSquares(world_->findActor("Enemy")->getPosition());

	// �}�X�ڂ��ς������
	if ((int)currentSquares_.x != (int)prevSquares_.x || (int)currentSquares_.y != (int)prevSquares_.y) {
		// 1�t���[���O�̃G���A��ݒ�
		prevArea_ = currentArea_;
		// ���݂̃G���A��ݒ�
		currentArea_ = CheckArea(currentSquares_);
		// �G�l�~�[���ړ����������G���A����Ȃ��ꍇ�ɏ���������
		if (std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"))->get_state() == EnemyBase::EnemyState::Move
			&& currentArea_ != prevArea_) {
			// �G���A�ɂ��m����ݒ�
			SetUp(CheckArea(currentSquares_));
			// �����m���𔻒�
			Change(eventProbability_.Judgment());
		}
	}
	currentRandomEvent_.lock()->Update();
	if (currentRandomEvent_.lock()->IsEnd()) {
		Change(currentRandomEvent_.lock()->Next());
	}
}

// �`��
void RandomEventManager::Draw() const
{
	currentRandomEvent_.lock()->Draw();
}

// ���W���}�X�ڂɕϊ�����
Vector2 RandomEventManager::ToSquares(const Vector3 & pos)
{
	auto row = ((pos.x) / 48.5f) + 1;
	auto col = ((27 - ((pos.z) / 48.5f)));

	// �C���f�b�N�X�O�ɂȂ�Ȃ����߂̏���
	if (row >= 28) row = 28;
	else if (row <= 1) row = 1;
	if (col >= 24) col = 24;
	else if (col <= 1) col = 1;

	return Vector2(row, col);
}

// �ǂ̃G���A�ɂ��邩�𔻒�
RandomEventArea RandomEventManager::CheckArea(const Vector2& pos)
{
	auto num = csvReader_.geti((int)pos.y - 1, (int)pos.x - 2);
	return static_cast<RandomEventArea>(num);
}

// �G���A�̊m����ݒ�
void RandomEventManager::SetUp(const RandomEventArea& area)
{
	probability_ = eventProbability_.SetUp(area);
}

// �����m���𔻒肷��
void RandomEventManager::Judgment()
{
	auto num = (std::rand() % 100) + 1;
}

// �f�o�b�O����
void RandomEventManager::DebugDraw()
{
#ifdef _DEBUG
	SetFontSize(32);
	/*DrawFormatString(10, 50, GetColor(255, 0, 0), "�c�F%i", (int)currentSquares_.y);
	DrawFormatString(10, 100, GetColor(255, 0, 0), "���F%i", (int)currentSquares_.x);*/
	switch (currentArea_) {
	case(RandomEventArea::None):DrawFormatString(10, 150, GetColor(255, 0, 0), "���݂̃G���A�F�ǂ��̃G���A�ɂ����܂���"); break;
	case(RandomEventArea::AreaBlue):DrawFormatString(10, 150, GetColor(255, 0, 0), "���݂̃G���A�F�G���A"); break;
	case(RandomEventArea::AreaGreen):DrawFormatString(10, 150, GetColor(255, 0, 0), "���݂̃G���A�F�΃G���A"); break;
	case(RandomEventArea::AreaRed):DrawFormatString(10, 150, GetColor(255, 0, 0), "���݂̃G���A�F�ԃG���A"); break;
	case(RandomEventArea::AreaOrange):DrawFormatString(10, 150, GetColor(255, 0, 0), "���݂̃G���A�F��G���A"); break;
	default:assert(!"����U���Ă��܂���"); break;
	}
	if (probability_.empty())return;
	DrawFormatString(10, 50, GetColor(255, 0, 0), "�����锭���m���F%f", probability_[0]);
	DrawFormatString(10, 100, GetColor(255, 0, 0), "�ʐM�����m���F%f", probability_[1]);
#endif // _DEBUG
}

// �I��
void RandomEventManager::End()
{
	if (currentRandomEvent_.expired())return;
	currentRandomEvent_.lock()->End();
}

// �����_���C�x���g�̒ǉ� 
void RandomEventManager::Add(RandomEvent name, const IRandomEventPtr & event)
{
	randomEvents_[name] = event;
}

// �����_���C�x���g�̕ύX   
void RandomEventManager::Change(RandomEvent name)
{
	End();
	currentRandomEvent_ = randomEvents_[name];
	currentRandomEvent_.lock()->Initialize();
}

void RandomEventManager::SetPosition(const Vector3 & position)
{
	currentSquares_ = ToSquares(position);
	prevSquares_ = currentSquares_;
	currentArea_ = CheckArea(currentSquares_);

}
