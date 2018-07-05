#pragma once
#include"../../../ID/EnumIDs.h"
#include<memory>
class EventState : public std::enable_shared_from_this<EventState> {
public:
	EventState();
	virtual ~EventState();
	virtual void start();
	virtual void update(float deltaTime);
	virtual void end();
	EventType getEventType()const;
private:
	EventType type_{EventType::EVENT_NULL};
	
};