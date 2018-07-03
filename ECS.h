#pragma once

#include "Util.h"
#include "Allocator.h"
#include "System.h"
#include "EventSubscriber.h"

#include <type_traits>
#include <typeinfo>
#include <typeindex>

namespace ECS {
	class ECS
	{
	public:
		ECS() {}

		void Update(float dt) {

		}

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

		/*template<typename EventType>
		void Subscribe() {
			
		}*/
	private:
		Allocator allocator;
		std::vector<std::unique_ptr<System>> systems;
	};
}
