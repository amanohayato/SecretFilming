#pragma once
#include"../Actor.h"
#include"../../UI/FieldMap.h"

// �}�b�v�A�v���̏��
enum class MapAppState
{
	// �X���[�v��
	Sleep,

	// �N����
	Active
};

class MapApp : public Actor
{
public:
	MapApp(IWorld * world, ActorPtr player);
	~MapApp();
	void initialize();

	void update(float deltaTime);

	void draw()const;

	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param) override;

	// �}�b�v�A�v���̏�Ԃ̕ύX
	void changeState(MapAppState state);

	void active();
	void sleep();
private:

	// ���݂̃}�b�v�A�v���̏��
	MapAppState curState_{ MapAppState::Sleep };
	FieldMap fieldMap_;
	// �e�v�f
	ActorPtr player_;

	int mapScreen_{ -1 };


};