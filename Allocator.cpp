#include "stdafx.h"
#include "Allocator.h"

namespace ECS {
	EntityIdentifier Allocator::CreateEntity()
	{
		EntityIdentifier id = id_generator.Generate();
		assert(entity_component_masks[id].none());
		return id;
	}

	void Allocator::DestroyEntity(EntityIdentifier id)
	{
		entity_component_masks[id].reset();
		id_generator.Free(id);
	}
}

