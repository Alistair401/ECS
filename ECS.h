#pragma once

#include "Util.h"
#include "Allocator.h"
#include "System.h"
#include "EventSubscriber.h"

#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <algorithm>

namespace ECS {
	class ECS
	{
	public:
		ECS() {}

		EntityID CreateEntity() {
			return allocator.CreateEntity();
		}

		void DestroyEntity(EntityID entity) {
			allocator.DestroyEntity(entity);
		}

		template <typename ComponentType, typename... TArgs>
		ComponentType& AddComponent(EntityID entity, TArgs... args) {
			return allocator.AddComponent<ComponentType>(entity, std::forward<TArgs>(args)...);
		}

		template<typename ComponentType>
		bool HasComponent(EntityID entity) {
			return allocator.HasComponent<ComponentType>();
		}

		template<typename ComponentType>
		void RemoveComponent(EntityID entity) {
			allocator.RemoveComponent<ComponentType>(entity);
		}

		template<typename SystemType, typename... TArgs>
		void AddSystem(TArgs... args) {
			static_assert(std::is_base_of<System, SystemType>::value, "SystemType must inherit from the System class");
			systems.emplace_back(new SystemType(std::forward<TArgs>(args)...));
			systems.back()->ecs = this;
			systems.back()->Init();
		}

		template<typename EventType>
		void Subscribe(EventSubscriber<EventType>* subscriber) {
			std::type_index index = typeid(EventType);
			auto found = event_subscribers.find(index);
			if (found == event_subscribers.end()) {
				event_subscribers[index] = std::vector<BaseEventSubscriber*>{ subscriber };
			}
			else {
				event_subscribers[index].push_back(subscriber);
			}
		}

		template<typename EventType>
		void Unsubscribe(EventSubscriber<EventType>* subscriber) {
			std::type_index index = typeid(EventType);
			auto found = event_subscribers.find(index);
			if (found != event_subscribers.end()) {
				found->second.erase(std::remove(found->second.begin(), found->second.end(), subscriber), found->second.end());
				if (found->second.size() == 0)
				{
					event_subscribers.erase(found);
				}
			}
		}

		template<typename EventType>
		void Notify(const EventType& event) {
			std::type_index index = typeid(EventType);
			auto found = event_subscribers.find(index);
			if (found != event_subscribers.end()) {
				for (BaseEventSubscriber* base : found->second) {
					auto* subscriber = static_cast<EventSubscriber<EventType>*>(base);
					subscriber->OnEvent(event);
				}
			}
		}

		void Update(float dt) {
			for (size_t i = 0; i < systems.size(); i++)
			{
				systems[i]->Update(dt);
			}
		}

	private:
		Allocator allocator;
		std::vector<std::unique_ptr<System>> systems;
		std::unordered_map<std::type_index, std::vector<BaseEventSubscriber*>> event_subscribers;
	};
}
