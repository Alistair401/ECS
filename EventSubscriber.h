#pragma once

namespace ECS {
	template<typename EventType>
	class EventSubscriber
	{
	public:
		virtual void OnEvent(const EventType& event) = 0;
	};
}
