#pragma once
#include "../../Actor.h"
#include "../../Enemy/EnemyBase.h"
#include "../../Player/State/PlayerState.h"

// �Q�[���I�[�o�[�C�x���g�N���X
// �S���FHo Siu Ki�i�����Q�j
// �Q�l�FActor/EventActor/GameClearEvent.h
class GameOverEvent : public Actor
{
public:
	// �R���X�g���N�^
	GameOverEvent(IWorld * world, float goal_timer, float goal_time, std::weak_ptr<EnemyBase> enemy);
	// ������
	void initialize();
	// �X�V
	void update(float delta_time) override;
	// �`��
	void draw()const;


private:
	std::function<void()> createUFOfunc_;
	std::weak_ptr<EnemyBase> enemy_;	// �G�l�~�[�̃|�C���^
	const float goal_time_;				// �S�[�����Ă��烊�U���g�Ɉڍs����܂ł̕b��
	float goal_timer_;					// �S�[�����Ă��烊�U���g�Ɉڍs����܂ł̕b���J�E���g
	const Vector3 camerapos_ = { 725.0f,11.0f,715.0f };
};