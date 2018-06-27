#pragma once
#include "Util.h"

#include "Component.h"

#include <vector>
#include <memory>
#include <array>

namespace ECS {

	class Allocator
	{
	public:
		EntityIdentifier CreateEntity();

		void SetToDestroyed(EntityIdentifier entity);

		void RemoveDestroyedEntities();
	private:
		EntityIdentifier next_id = 0;
		std::array<std::vector<std::unique_ptr<Component>>, MAX_COMPONENTS> component_array;
		std::vector<ComponentBitset> entity_component_masks;
		std::vector<EntityIdentifier> entities_to_destroy;
	};
}
