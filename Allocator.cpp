#include "stdafx.h"
#include "Allocator.h"

namespace ECS {
	EntityID Allocator::CreateEntity()
	{
		EntityID id = id_generator.Generate();
		assert(entity_component_masks[id].none());
		return id;
	}

	void Allocator::DestroyEntity(EntityID id)
	{
		entity_component_masks[id].reset();
		id_generator.Free(id);
	}
}

