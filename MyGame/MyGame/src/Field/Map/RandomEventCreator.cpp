#include "RandomEventCreator.h"
#include"../Building/SendEventToEnemy.h"
#include"../../World/IWorld.h"
#include"../../Math/Random.h"
#include<map>


RandomEventCreator::RandomEventCreator()
{
}

void RandomEventCreator::initialize(const Point& fieldSize)
{
	int firstNum = Random::GetInstance().Range(0, (int)eventRoute_.size() - 1);
	int addNum = Random::GetInstance().Range(0, 1) ? -1 : 1;
	for (int i = 0; i < eventRoute_.size(); i++) {
		eventRoute_[i] = firstNum;
		firstNum += addNum;
		firstNum = (firstNum + (int)eventRoute_.size()) % (int)eventRoute_.size();
	}
	//for (int i = 0; i < eventRoute_.size(); i++)
	//{
	//	int j = rand() % eventRoute_.size();
	//	int t = eventRoute_[i];
	//	eventRoute_[i] = eventRoute_[j];
	//	eventRoute_[j] = t;
	//}
	fieldSize_ = fieldSize;
}

void RandomEventCreator::add(const Vector3 & position, std::weak_ptr<BuildingBase> building)
{
	int xSlice = fieldSize_.x / 2;
	int ySlice = fieldSize_.y / 3;

	int xResult = (int)position.x / xSlice;
	int yResult = (int)position.z / ySlice;

	//
	int returnNum = xResult > 0 ? -1 : 1;
	int block = (xResult * (3 + 2)) + (yResult*returnNum);
	block = MathHelper::Clamp(block, 0, (int)eventRoute_.size() - 1);

	EventPoint evp;
	evp.building_ = building;
	evp.position_ = position;
	evp.block_ = block;
	events_.push_back(std::make_pair(block, evp));
}

void RandomEventCreator::chooseEvent(IWorld* world)
{
	//6区画にイベントを1つずつ設定する=合計6個のイベントを設定する
	//6区画はそれぞれ1個以上のイベントを持つ=それぞれの区画で、その中からイベントを選ぶ
	//決定した6個のイベントは、重複しないようにする

	//各イベントが何番にあるかを調べる
	//各イベントが全ブロックに配置出来るようにする

	events_.sort([](std::pair<int, EventPoint>& iep1, std::pair<int, EventPoint>& iep2) {
		return iep1.first < iep2.first;
	});

	std::array<std::list<EventType>, 6> eventtypes{};
	for (auto& e : events_) {
		//イベントタイプの取得
		eventtypes[e.first].push_back(e.second.building_.lock()->getEvent());
	}
	//イベントの重複を削除
	for (auto& e : eventtypes) {
		e.sort();
		e.unique();
	}

	std::map<EventType, int> eventOverrapCount{
		{ EventType::EVENT_POLICE,0 },
	{ EventType::EVENT_TAKOYAKIYA,0 },
	{ EventType::EVENT_BACKSTREET_RATI,0 },
	{ EventType::EVENT_BACKSTREET_KAIWA,0 },
	{ EventType::EVENT_JUNCTION,0 },
	{ EventType::EVENT_VENDING,0 },
	{ EventType::EVENT_SMOKING,0 },
	{ EventType::EVENT_FISHSTORE,0 },
	{ EventType::EVENT_MANHORU,0 },
	};

	for (auto& etl : eventtypes) {
		for (auto& et : etl) {
			eventOverrapCount[et]++;
		}
	}
	std::list<std::pair<EventType, int>> eventOverraplist;
	for (auto& eoc : eventOverrapCount) {
		eventOverraplist.push_back(std::make_pair(eoc.first, eoc.second));
	}
	eventOverraplist.sort([](std::pair<EventType, int>& one, std::pair<EventType, int>& two) {
		return one.second > two.second;
	});
	eventOverraplist.remove_if([](auto& ev) {return ev.second == 0; });

	//eventsの区画ごとのイベントリスト
	std::array<EventType, 6> events{
		EventType::EVENT_NULL,
		EventType::EVENT_NULL,
		EventType::EVENT_NULL,
		EventType::EVENT_NULL,
		EventType::EVENT_NULL,
		EventType::EVENT_NULL
	};
	while (true)
	{
		if (std::find(events.begin(), events.end(), EventType::EVENT_NULL) == events.end())break;
		auto targetevent = eventOverraplist.front();

		bool isSuccess = false;
		for (int etcount = 0; etcount < eventtypes.size(); etcount++) {
			if (events[etcount] != EventType::EVENT_NULL)continue;
			auto ev = std::find(eventtypes[etcount].begin(), eventtypes[etcount].end(), targetevent.first);
			if (ev != eventtypes[etcount].end()) {
				events[etcount] = targetevent.first;
				isSuccess = true;
				break;
			}
		}
		if (!isSuccess) {
			for (int ec = 0; ec < events.size(); ec++) {
				if (events[ec] == EventType::EVENT_NULL) {
					int ev = Random::GetInstance().Range(0, (int)eventtypes[ec].size() - 1);
					auto evitr = eventtypes[ec].begin();
					for (int i = 0; i < ev; i++) { evitr++; }
					auto isevAlready = std::find(events.begin(), events.end(), *evitr);
					if (isevAlready != events.end())*isevAlready = EventType::EVENT_NULL;
					events[ec] = *evitr;
					eventOverraplist.push_back(targetevent);
					break;
				}
			}
			/*for (int etcount = 0; etcount < eventtypes.size(); etcount++) {
				auto ev = std::find(eventtypes[etcount].begin(), eventtypes[etcount].end(), targetevent.first);
				if (ev != eventtypes[etcount].end()) {
					eventOverraplist.push_back(std::make_pair(events[etcount], 1));
					events[etcount] = targetevent.first;
					break;
				}
			}*/
		}
		eventOverraplist.pop_front();
	}

	std::map<int, EventPoint> targetBuildingMap;

	for (int i = 0; i < events.size(); i++) {
		std::vector<EventPoint> targetBuildings;
		for (auto& e : events_) {
			if (e.first == i && e.second.building_.lock()->getEvent() == events[i]) {
				///ここでマンホールのイベントの特別なpositionを代入
				if (e.second.building_.lock()->getEvent() == EventType::EVENT_MANHORU) {
					auto pos = e.second.building_.lock()->getPosition();
					e.second.position_ = pos + e.second.building_.lock()->getPose().Forward()*10.0f;
					e.second.position2_ = pos + e.second.building_.lock()->getPose().Backward()*10.0f;
				}
				targetBuildings.push_back(e.second);
			}
		}
		int target = Random::GetInstance().Range(0, (int)targetBuildings.size() - 1);
		targetBuildingMap[i] = targetBuildings[target];
	}

	for (int i = 0; i < targetBuildingMap.size(); i++) {
		world->addEventList(targetBuildingMap[eventRoute_[i]]);
	}

	auto a = world->getEventList();


	//for (int i = 0; i < events.size(); i++) {
	//	int accessNum = Random::GetInstance().Range(0, eventtypes[i].size()-1);
	//	std::list<EventType>::iterator etitr = eventtypes[i].begin();
	//	for (int i = 0; i < accessNum; i++) {
	//		etitr++;
	//	}
	//	events[i] = *etitr;
	//}
	//
	////実際に巡回イベントを決定
	//std::array<EventPoint,6> addEventsList;
	//for (int i = 0; i < events.size();i++) {
	//	
	//	auto result= std::find_if(events_.begin(), events_.end(), [&](std::pair<int, EventPoint>& piet) {
	//		return piet.first == i&&events[i] == piet.second.building_.lock()->getEvent();
	//	});
	//	addEventsList[i] = result->second;
	//}
	//for (int i = 0; i < addEventsList.size(); i++) {
	//	world->addEventList(addEventsList[eventRoute_[i]]);

	//}
	//auto a = world->getEventList();

	////while (!eventtypes.empty()) {
	////	//0番を抜き出す
	////	auto currentET = eventtypes.front();
	////	eventtypes.erase(eventtypes.begin());

	////	//findで、他のブロックに存在しないイベントを探す
	////	for (auto et : currentET) {
	////		for (auto ets : eventtypes) {
	////			std::find(ets.begin(), ets.end(), et);

	////		}
	////	}
	////}

	////for (auto& e : events_) {
	////	world->addEventList(e.second);
	////}



}
