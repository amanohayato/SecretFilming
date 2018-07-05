#pragma once

#include <unordered_map>
#include <algorithm>

#include "../../World/IWorld.h"



class Event;

class EventManager {
public:
	//イベントの種類
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
	//コンストラクタ
	EventManager(IWorld& world);
	~EventManager();
	//イベントを追加する(イベントの種類、イベントクラス)
	void AddEvent(const EventState& state, Event* e);
	////イベントを変える(強制的に終了させる場合は仕様を見て考える)
	//void ChangeEvent(const EventState& state);
	//現在のイベントの取得
	EventState GetEvent();
	//現在のイベントが進行しているか
	bool GetIsNowEvent();
	//イベントアップデート
	void Update();
	//描写
	void Draw();
private:
	//ワールド
	IWorld* mWorld;
	//現在のイベント
	EventState mNowEventState;
	//イベントが進行しているか
	bool mIsNowEvent;

	//イベントたち
	std::vector<std::pair<EventState, Event*>> mEvents;

	//イベントの進み番号
	int mEventIndex;

	////イベントたち
	//std::unordered_map<EventState, Event*> mEvents;
};