#pragma once

#include <vector>
#include <memory>


namespace ECS {
	class ComponentManager
	{
	public:
		//template <typename ComponentType, typename... TArgs>
		//void AddComponent(EntityIdentifier entity, TArgs&&... args) {
		//	TypeIdentifier component_type_identifier = ECS::GetTypeIdentifier<ComponentType>();

		//	assert(!HasComponent<ComponentType>(entity));

		//	ComponentType* component_instance = new ComponentType(std::forward<TArgs>(args)...);
		//	entity_components[entity].emplace_back(std::move(component_instance));
		//	entity_component_masks[entity][component_type_identifier] = true;
		//}

		/*template <typename ComponentType>
		void RemoveComponent(EntityIdentifier entity) {
			TypeIdentifier component_type_identifier = ECS::GetTypeIdentifier<ComponentType>();
			
			assert(!HasComponent<ComponentType>(entity));

		}*/

		/*template <typename ComponentType>
		bool HasComponent(EntityIdentifier entity) {
			TypeIdentifier component_type_identifier = ECS::GetTypeIdentifier<ComponentType>();

			return entity_component_masks[entity][component_type_identifier];
		}*/

		/*template <typename ComponentType>
		Component& GetComponent() {
			TypeIdentifier component_type_identifier = ECS::GetTypeIdentifier<ComponentType>();
			
			assert(!HasComponent<ComponentType>(entity));

			return *entity_components[entity][component_type_identifier];
		}*/
	private:
		//std::vector<ComponentBitset> entity_component_masks;
		//std::vector<std::vector<std::unique_ptr<Component>>> entity_components;
	};
}