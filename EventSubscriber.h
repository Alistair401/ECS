#pragma once

#include "BaseEventSubscriber.h"

namespace ECS {
	template<typename EventType>
	class EventSubscriber : public BaseEventSubscriber
	{
	public:
		virtual void OnEvent(const EventType& event) = 0;
	};
}
