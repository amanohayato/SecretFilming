#include "EventManager.h"

#include "../Event/Event.h"

#include "../EventActor/_ShareEventActor/KizukiEventActor.h"
#include "../EventActor/_ShareEventActor/MimawasiEventActor.h"

#include "../../Event/EventActor/PoliceEvent/01/PoliceEventActor01.h"
#include "../../Event/EventActor/PoliceEvent/02/PoliceEventActor02.h"
#include "../../Event/EventActor/PoliceEvent/03/PoliceEventActor03.h"
#include "../../Event/EventActor/PoliceEvent/04/PoliceEventActor04.h"
#include "../../Event/EventActor/PoliceEvent/05/PoliceEventActor05.h"
#include "../../Event/EventActor/PoliceEvent/06/PoliceEventActor06.h"
#include "../../Event/EventActor/PoliceEvent/07/PoliceEventActor07.h"
#include "../../Event/EventActor/PoliceEvent/08/PoliceEventActor08.h"


#include "../../Event/EventActor/ManhoruEvent/02/ManhoruEventActor02.h"
#include "../../Event/EventActor/ManhoruEvent/03/ManhoruEventActor03.h"
#include "../../Event/EventActor/ManhoruEvent/04/ManhoruEventActor04.h"
#include "../../Event/EventActor/ManhoruEvent/05/ManhoruEventActor05.h"
#include "../../Event/EventActor/ManhoruEvent/06/ManhoruEventActor06.h"
#include "../../Event/EventActor/ManhoruEvent/07/ManhoruEventActor07.h"
#include "../../Event/EventActor/ManhoruEvent/08/ManhoruEventActor08.h"
#include "../../Event/EventActor/ManhoruEvent/09/ManhoruEventActor09.h"
#include "../../Event/EventActor/ManhoruEvent/10/ManhoruEventActor10.h"


#include  "../EventActor/ZihankiEvent/01/ZihankiEventActor01.h"
#include  "../EventActor/ZihankiEvent/02/ZihankiEventActor02.h"
#include  "../EventActor/ZihankiEvent/03/ZihankiEventActor03.h"
#include  "../EventActor/ZihankiEvent/04/ZihankiEventActor04.h"
#include  "../EventActor/ZihankiEvent/05/ZihankiEventActor05.h"
#include  "../EventActor/ZihankiEvent/06/ZihankiEventActor06.h"

#include "../EventActor/KituenzyoEvent/01/KituenzyoEventActor01.h"
#include "../EventActor/KituenzyoEvent/02/KituenzyoEventActor02.h"
#include "../EventActor/KituenzyoEvent/03/KituenzyoEventActor03.h"
#include "../EventActor/KituenzyoEvent/04/KituenzyoEventActor04.h"
#include "../EventActor/KituenzyoEvent/05/KituenzyoEventActor05.h"

#include "../EventActor/JunctionEvent/01/JunctionEventActor01.h"
#include "../EventActor/JunctionEvent/02/JunctionEventActor02.h"
#include "../EventActor/JunctionEvent/03/JunctionEventActor03.h"
#include "../EventActor/JunctionEvent/04/JunctionEventActor04.h"

#include "../EventActor/_ShareEventActor/MimawasiEventActor.h"

#include "../EventActor/KaiwaEvent/01/KaiwaEventActor01.h"
#include "../EventActor/KaiwaEvent/02/KaiwaEventActor02.h"

#include "../EventActor/NekoEvent/01/NekoEventActor01.h"
#include "../EventActor/NekoEvent/02/NekoEventActor02.h"
#include "../EventActor/NekoEvent/03/NekoEventActor03.h"

#include "../../Actor/Enemy/EnemyBase.h"


#include "../../Field/WalkGraph.h"

EventManager::EventManager(IWorld & world) :
	mWorld(&world),
	mNowEventState(EventState::NULL_EVENT),
	mEventIndex(0)
{


	auto enemyBase = static_cast<EnemyBase*>(world.findActor("Enemy").get());
	auto eventPoints = enemyBase->GetEventPoints();

	for (const auto& i : eventPoints) {
		auto eventEnum = EventState::NULL_EVENT;
		switch (i.building_.lock()->getEvent())
		{
		case EventType::EVENT_POLICE:
		{
			eventEnum = EventState::POLICE_EVENT;

			auto test = new Event(world);

			test->Add(new PoliceEventActor01(world));
			test->Add(new PoliceEventActor02(world));
			test->Add(new PoliceEventActor03(world));
			test->Add(new PoliceEventActor04(world));
			test->Add(new PoliceEventActor05(world));
			test->Add(new PoliceEventActor06(world));
			test->Add(new PoliceEventActor07(world));
			test->Add(new PoliceEventActor08(world));
			test->Add(new MimawasiEventActor(world));


			AddEvent(EventState::POLICE_EVENT, test);

			break;
		}
		case EventType::EVENT_MANHORU:
		{
			auto test = new Event(world);
			AddEvent(EventState::MANHORU_EVENT, test);

			test->Add(new KizukiEventActor(world, i.building_.lock()->getEvent()));

			test->Add(new ManhoruEventActor02(world));
			test->Add(new ManhoruEventActor03(world));
			test->Add(new ManhoruEventActor04(world));
			test->Add(new ManhoruEventActor05(world));
			test->Add(new ManhoruEventActor06(world));
			test->Add(new ManhoruEventActor07(world));
			test->Add(new ManhoruEventActor08(world));
			test->Add(new ManhoruEventActor09(world));
			test->Add(new ManhoruEventActor10(world));


			test->Add(new MimawasiEventActor(world));
			eventEnum = EventState::MANHORU_EVENT;
			break;
		}
		case EventType::EVENT_VENDING:
		{
			//テスト用にここにイベント追加する
			auto test = new Event(world);
			//イベントアクター追加
			test->Add(new KizukiEventActor(world, EventType::EVENT_VENDING));
			test->Add(new ZihankiEventActor01(world));
			test->Add(new ZihankiEventActor02(world));
			test->Add(new ZihankiEventActor03(world));
			test->Add(new ZihankiEventActor04(world));
			test->Add(new ZihankiEventActor05(world));
			test->Add(new MimawasiEventActor(world));
			AddEvent(EventState::ZIHANKI_EVENT, test);
			eventEnum = EventState::ZIHANKI_EVENT;
			break;
		}
		case EventType::EVENT_SMOKING:
		{
			//テスト用にここにイベント追加する
			auto test = new Event(world);
			//イベントアクター追加
			test->Add(new KizukiEventActor(world, EventType::EVENT_SMOKING));
			test->Add(new KituenzyoEventActor02(world));
			test->Add(new KituenzyoEventActor03(world));
			test->Add(new KituenzyoEventActor04(world));
			test->Add(new KituenzyoEventActor05(world));
			test->Add(new MimawasiEventActor(world));
			eventEnum = EventState::KITUEN_EVENT;
			AddEvent(EventState::KITUEN_EVENT, test);
			break;
		}
		case EventType::EVENT_JUNCTION:
		{
			//テスト用にここにイベント追加する
			auto test = new Event(world);
			//イベントアクター追加
			test->Add(new KizukiEventActor(world, EventType::EVENT_JUNCTION));
			test->Add(new JunctionEventActor01(world));
			test->Add(new JunctionEventActor02(world));
			test->Add(new JunctionEventActor04(world));
			test->Add(new JunctionEventActor03(world));
			test->Add(new MimawasiEventActor(world));
			eventEnum = EventState::KOUSATEN_EVENT;
			AddEvent(EventState::KOUSATEN_EVENT, test);
			break;
		}
		case EventType::EVENT_NEKO: {
			//テスト用にここにイベント追加する
			auto test = new Event(world);
			//イベントアクター追加
			test->Add(new KizukiEventActor(world, EventType::EVENT_NEKO));
			test->Add(new NekoEventActor01(world));
			test->Add(new NekoEventActor02(world));
			test->Add(new NekoEventActor03(world));
			test->Add(new MimawasiEventActor(world));
			eventEnum = EventState::NEKO_EVENT;
			AddEvent(EventState::NEKO_EVENT, test);
			break;
		}
		default: {
			//テスト用にここにイベント追加する
			auto test = new Event(world);
			test->Add(new KizukiEventActor(world, i.building_.lock()->getEvent()));
			test->Add(new MimawasiEventActor(world));
			eventEnum = EventState::NULL_EVENT;
			AddEvent(EventState::NULL_EVENT, test);

			break;
		}
		}
	}
	int a = 0;
	//test->Add(new ZihankiEventActor01(world));
	//test->Add(new ZihankiEventActor02(world));
	//test->Add(new ZihankiEventActor03(world));
	//test->Add(new ZihankiEventActor04(world));
	//test->Add(new ZihankiEventActor05(world));
	//test->Add(new ZihankiEventActor06(world));

	auto graph = world.getWalkMap();
	auto nodes = graph.getNode(0);



}

EventManager::~EventManager()
{

}
void EventManager::AddEvent(const EventState & state, Event* e)
{
	std::pair<EventState, Event*> events;
	events.first = state;
	events.second = e;
	mEvents.push_back(events);
}

//void EventManager::ChangeEvent(const EventState & state)
//{
//	//イベントが進行中の場合イベントリセット関数
//	if (!mEvents[state]->GetIsEventEnd())
//		mEvents[state]->ResetEvent();
//	mNowEventState = state;
//}

EventManager::EventState EventManager::GetEvent()
{
	return mNowEventState;
}

bool EventManager::GetIsNowEvent()
{
	return mIsNowEvent;
}

void EventManager::Update()
{
	if (mEventIndex >= mEvents.size())return;

	//イベントが終わったら消してNULLイベントにする
	if (mEvents[mEventIndex].second->GetIsEventEnd()) {
		delete mEvents[mEventIndex].second;
		//終わったらインデックスを＋
		mEventIndex++;
		return;
	}
	mEvents[mEventIndex].second->Update();
}

void EventManager::Draw()
{
	if (mEventIndex >= mEvents.size())return;

	mEvents[mEventIndex].second->Draw();
}
