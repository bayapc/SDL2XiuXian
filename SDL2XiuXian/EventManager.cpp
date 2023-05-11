#include "EventManager.h"

EventManager* EventManager::instance = NULL;
EventManager* EventManager::get_instance(void)
{
	if (instance == NULL) {
		instance = new EventManager();
	}
	return instance;
}
void EventManager::register_event_type(Actor* a, std::string name)
{
	uid_map.insert(std::make_pair(name,a->get_uid()));
	actor_map.insert(std::make_pair(a->get_uid(),ActorEvent()));
}
void EventManager::deregister_event_type(Actor* a)
{
	for (auto it = uid_map.begin(); it != uid_map.end(); it++) {
		if (it->second == a->get_uid()) {
			uid_map.erase(it);
			break;
		}
	}
	for (auto it = actor_map.begin(); it != actor_map.end(); it++) {
		if (it->first == a->get_uid()) {
			actor_map.erase(it);
			break;
		}
	}
}
void EventManager::dispatch_event(ActorEvent event)
{
	//actor_map[event.uid] = event;
	for (auto it = actor_map.begin(); it != actor_map.end(); it++) {
		if (it->first == event.uid) {
			it->second = event;
			std::cout << "dispatch" << event.uid<<"ok"<< std::endl;
			break;
		}
	}
}
ActorEvent EventManager::get_event(Actor* a)
{
	ActorEvent tmp;
	ActorEvent empty = { 0,KEY_IDLE,{0,0} };
	for (auto it = actor_map.begin(); it != actor_map.end(); it++) {
		if (it->first == a->get_uid()) {
			if (it->second.uid != 0) {
				tmp = it->second;
				std::cout << "get event" << a->get_uid() << "ok" << std::endl;
				/* clean event*/
				it->second = empty;
				return tmp;
			}else {
				//return empty
				break;
			}
		}
	}
	return empty;
}

Uint32 EventManager::get_uid_by_name(std::string name)
{
	for (auto it = uid_map.begin(); it != uid_map.end(); it++) {
		if (it->first == name) {
			return it->second;
		}
	}
	return 0;
}


