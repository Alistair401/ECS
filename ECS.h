#pragma once

#include "Util.h"
#include "Allocator.h"
#include "System.h"

#include <type_traits>

namespace ECS {
	class ECS
	{
	public:
		ECS() {}

		void Update(float dt) {

		}

		EntityIdentifier CreateEntity() {
			return allocator.CreateEntity();
		}

		void DestroyEntity(EntityIdentifier entity) {
			allocator.DestroyEntity(entity);
		}

		template <typename ComponentType, typename... TArgs>
		ComponentType& AddComponent(EntityIdentifier entity, TArgs... args) {
			return allocator.AddComponent<ComponentType>(entity, std::forward<TArgs>(args)...);
		}

		template<typename ComponentType>
		bool HasComponent(EntityIdentifier entity) {
			return allocator.HasComponent<ComponentType>();
		}

		template<typename ComponentType>
		void RemoveComponent(EntityIdentifier entity) {
			allocator.RemoveComponent<ComponentType>(entity);
		}
	private:
		Allocator allocator;
		std::vector<System> systems;
	};
}
