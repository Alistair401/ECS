#pragma once
#include "Util.h"

#include "Component.h"
#include "IDGenerator.h"

#include <vector>
#include <memory>
#include <array>
#include <functional>

namespace ECS {

	class Allocator
	{
	public:
		EntityID CreateEntity();

		void DestroyEntity(EntityID entity);

		template <typename ComponentType, typename... TArgs>
		ComponentType& AddComponent(EntityID entity, TArgs... args) {
			assert(!HasComponent<ComponentType>(entity));

			ComponentID component_id = GetComponentIdentifier<ComponentType>();

			component_array[component_id][entity] = std::make_unique<ComponentType>(std::forward<TArgs>(args)...);
			entity_component_masks[entity][component_id] = true;

			ComponentType* ptr = static_cast<ComponentType*>(component_array[component_id][entity].get());
			return *ptr;
		}

		template<typename ComponentType>
		bool HasComponent(EntityID entity) {
			ComponentID component_id = GetComponentIdentifier<ComponentType>();

			return entity_component_masks[entity][component_id];
		}

		template<typename ComponentType>
		void RemoveComponent(EntityID entity) {
			assert(HasComponent<ComponentType>(entity));

			ComponentID component_id = GetComponentIdentifier<ComponentType>();

			component_array[component_id][entity] = nullptr;
			entity_component_masks[entity][component_id] = false;
		}

		template<typename ComponentType>
		ComponentType& GetComponent(EntityID entity) {
			assert(HasComponent<ComponentType>(entity));

			ComponentID component_id = GetComponentIdentifier<ComponentType>();

			ComponentType* ptr = static_cast<ComponentType*>(component_array[component_id][entity].get());
			return *ptr;
		}

		template<typename... ComponentTypes>
		void Each(std::function<void(EntityID, ComponentTypes&...)> transformation) {
			std::vector<ComponentID> component_ids = { (GetComponentIdentifier<ComponentTypes>())... };

			ComponentBitset component_mask;
			for (ComponentID id : component_ids)
			{
				component_mask[id] = true;
			}

			for (EntityID entity_id = 0; entity_id < MAX_ENTITIES; entity_id++)
			{
				if ((entity_component_masks[entity_id] & component_mask) == component_mask) {
					std::tuple<EntityID, ComponentTypes&...> components = { entity_id, (GetComponentUnsafe<ComponentTypes>(entity_id))... };
					std::apply(transformation, components);
				}
			}
		}
	private:
		std::array<std::array<std::unique_ptr<Component>, MAX_ENTITIES>, MAX_COMPONENTS> component_array;
		std::array<ComponentBitset, MAX_ENTITIES> entity_component_masks;
		IDGenerator id_generator{ MAX_ENTITIES };

		template<typename ComponentType>
		ComponentType& GetComponentUnsafe(EntityID entity) {
			ComponentID component_id = GetComponentIdentifier<ComponentType>();
			ComponentType* ptr = static_cast<ComponentType*>(component_array[component_id][entity].get());
			return *ptr;
		}
	};
}
