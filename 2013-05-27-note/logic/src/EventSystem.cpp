﻿#include "../include/EventSystem.h"
#include "../include/LoggerSystem.h"


std::string  _to_event_param_(bool param)
{
	char buffer[16] = "";
	sprintf(buffer, "%u", param);
	return buffer;
}

std::string  _to_event_param_(char param)
{
	char buffer[16] = "";
	sprintf(buffer, "%c", param);
	return buffer;
}

std::string  _to_event_param_(unsigned char param)
{
	char buffer[16] = "";
	sprintf(buffer, "%c", param);
	return buffer;
}

std::string  _to_event_param_(short param)
{
	char buffer[16] = "";
	sprintf(buffer, "%c", param);
	return buffer;
}

std::string  _to_event_param_(unsigned short param)
{
	char buffer[16] = "";
	sprintf(buffer, "%u", param);
	return buffer;
}

std::string  _to_event_param_(int param)
{
	char buffer[16] = "";
	sprintf(buffer, "%d", param);
	return buffer;
}

std::string  _to_event_param_(unsigned int param)
{
	char buffer[16] = "";
	sprintf(buffer, "%u", param);
	return buffer;
}

std::string  _to_event_param_(float param)
{
	char buffer[16] = "";
	sprintf(buffer, "%f", param);
	return buffer;
}

std::string  _to_event_param_(double param)
{
	char buffer[16] = "";
	sprintf(buffer, "%f", param);
	return buffer;
}

std::string  _to_event_param_(char* param)
{
	return std::string(param);
}

std::string  _to_event_param_(const char* param)
{
	return std::string(param);
}

std::string  _to_event_param_(long long param)
{
	char buffer[64] = "";
	sprintf(buffer, "%lld", param);
	return buffer;
}

template<> EventSystem* cobra_win::Singleton2<EventSystem>::m_pMySelf = NULL;

EventSystem::EventSystem()
{

}

EventSystem::~EventSystem()
{

}

void EventSystem::RegisterEventHandler(int iEventType, pEventHandler pMyEventHandler)
{
	std::string str = "";
	RegisterEventHandler(iEventType, pMyEventHandler, str);
}

void EventSystem::RegisterEventHandler(int iEventType, pEventHandler pMyEventHandler, std::string owerData)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter != m_EventHandlerList.end())
	{
		iter->second.mEventHandlerList.insert(std::multimap<pEventHandler, std::string>::value_type(pMyEventHandler, owerData));
		return ;
	}

	_EVENT_ event;
	event.mEventID = iEventType;
	event.mEventHandlerList.insert(std::multimap<pEventHandler, std::string>::value_type(pMyEventHandler, owerData));
	m_EventHandlerList.insert(std::map<int, _EVENT_>::value_type(iEventType, event));
}

void EventSystem::UnRegisterEventHandler(int iEventType, pEventHandler pMyEventHandler)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.find(pMyEventHandler);
	if (iter2 == iter->second.mEventHandlerList.end())
		return ;

	iter->second.mEventHandlerList.erase(iter2);
}

void EventSystem::PushEvent(int iEventType)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.clear();

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);
		paramList.push_back(param5);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);
		paramList.push_back(param5);
		paramList.push_back(param6);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);
		paramList.push_back(param5);
		paramList.push_back(param6);
		paramList.push_back(param7);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);
		paramList.push_back(param5);
		paramList.push_back(param6);
		paramList.push_back(param7);
		paramList.push_back(param8);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

void EventSystem::PushEvent(int iEventType, std::string param1, std::string param2, std::string param3, std::string param4, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
{
	std::map<int, _EVENT_>::iterator iter = m_EventHandlerList.find(iEventType);
	if (iter == m_EventHandlerList.end())
		return ;

	std::multimap<pEventHandler, std::string>::iterator iter2   = iter->second.mEventHandlerList.begin();
	std::multimap<pEventHandler, std::string>::iterator iter2_e = iter->second.mEventHandlerList.end();
	for ( ; iter2!=iter2_e; ++iter2)
	{
		std::list<std::string> paramList;
		paramList.push_back(param1);
		paramList.push_back(param2);
		paramList.push_back(param3);
		paramList.push_back(param4);
		paramList.push_back(param5);
		paramList.push_back(param6);
		paramList.push_back(param7);
		paramList.push_back(param8);
		paramList.push_back(param9);

		iter2->first(iEventType, iter2->second, paramList);
	}
}

bool EventSystem::Init()
{
	LOGGERSYSTEM->LogInfo("Init EventSystem Success\n");
	return true;
}

void EventSystem::Tick()
{

}

void EventSystem::Destroy()
{
	std::map<int, _EVENT_>::iterator iter   = m_EventHandlerList.begin();
	std::map<int, _EVENT_>::iterator iter_e = m_EventHandlerList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		iter->second.mEventHandlerList.clear();
	}
	m_EventHandlerList.clear();

	LOGGERSYSTEM->LogInfo("Destroy EventSystem Success\n");
}
