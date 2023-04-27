#pragma once
#include "Global.h"
#include "Actor.h"

class EventManager
{
public:
	static EventManager* get_instance(void);
	void register_event_type(Actor* a,std::string name);
	void deregister_event_type(Actor* a);
	void dispatch_event(ActorEvent event);
	ActorEvent get_event(Actor* a);
	Uint32 get_uid_by_name(std::string name);

private:
	EventManager() {}
	~EventManager() {}

	static EventManager* instance;
	/**/
	std::map<std::string, Uint32> uid_map;
	std::map<Uint32,ActorEvent> actor_map;
};

