#pragma once

#include <unordered_map>
#include <algorithm>

#include "../../World/IWorld.h"



class Event;

class EventManager {
public:
	//�C�x���g�̎��
	enum EventState
	{
		NULL_EVENT,
		ZIHANKI_EVENT,
		KITUEN_EVENT,
		KOUSATEN_EVENT,
		MANHORU_EVENT,
		POLICE_EVENT,
		NEKO_EVENT,
	};

public:
	//�R���X�g���N�^
	EventManager(IWorld& world);
	~EventManager();
	//�C�x���g��ǉ�����(�C�x���g�̎�ށA�C�x���g�N���X)
	void AddEvent(const EventState& state, Event* e);
	////�C�x���g��ς���(�����I�ɏI��������ꍇ�͎d�l�����čl����)
	//void ChangeEvent(const EventState& state);
	//���݂̃C�x���g�̎擾
	EventState GetEvent();
	//���݂̃C�x���g���i�s���Ă��邩
	bool GetIsNowEvent();
	//�C�x���g�A�b�v�f�[�g
	void Update();
	//�`��
	void Draw();
private:
	//���[���h
	IWorld* mWorld;
	//���݂̃C�x���g
	EventState mNowEventState;
	//�C�x���g���i�s���Ă��邩
	bool mIsNowEvent;

	//�C�x���g����
	std::vector<std::pair<EventState, Event*>> mEvents;

	//�C�x���g�̐i�ݔԍ�
	int mEventIndex;

	////�C�x���g����
	//std::unordered_map<EventState, Event*> mEvents;
};