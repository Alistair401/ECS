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

	private:
		Allocator allocator;
	};
}
