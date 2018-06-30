#pragma once
#include "Util.h"

#include "Component.h"
#include "IDGenerator.h"

#include <vector>
#include <memory>
#include <array>

namespace ECS {

	class Allocator
	{
	public:
		EntityIdentifier CreateEntity();

		void DestroyEntity(EntityIdentifier entity);

		template <typename ComponentType, typename... TArgs>
		ComponentType& AddComponent(EntityIdentifier entity, TArgs... args) {
			assert(!HasComponent<ComponentType>(entity));

			ComponentIdentifier component_id = GetComponentIdentifier<ComponentType>();

			component_array[component_id][entity] = std::make_unique<ComponentType>(std::forward<TArgs>(args)...);
			entity_component_masks[entity][component_id] = true;

			ComponentType* ptr = static_cast<ComponentType*>(component_array[component_id][entity].get());
			return *ptr;
		}

		template<typename ComponentType>
		bool HasComponent(EntityIdentifier entity) {
			ComponentIdentifier component_id = GetComponentIdentifier<ComponentType>();

			return entity_component_masks[entity][component_id];
		}

		template<typename ComponentType>
		void RemoveComponent(EntityIdentifier entity) {
			assert(!HasComponent<ComponentType>(entity));

			ComponentIdentifier component_id = GetComponentIdentifier<ComponentType>();

			component_array[component_id][entity] = nullptr;
			entity_component_masks[entity][component_id] = false;
		}

		template<typename ComponentType>
		ComponentType& GetComponent(EntityIdentifier entity) {
			assert(!HasComponent<ComponentType>(entity));

			ComponentIdentifier component_id = GetComponentIdentifier<ComponentType>();

			ComponentType* ptr = static_cast<ComponentType*>(component_array[component_id][entity].get());
			return *ptr;
		}
	private:
		std::array<std::array<std::unique_ptr<Component>, MAX_ENTITIES>, MAX_COMPONENTS> component_array;
		std::array<ComponentBitset, MAX_ENTITIES> entity_component_masks;
		IDGenerator id_generator{ MAX_ENTITIES };
	};
}
