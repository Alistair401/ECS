#include "stdafx.h"
#include "Allocator.h"

namespace ECS {
	EntityIdentifier Allocator::CreateEntity()
	{
		for (size_t i = 0; i < MAX_COMPONENTS; i++)
		{
			component_array[i].emplace_back(nullptr);
		}
		return next_id++;
	}

	void Allocator::SetToDestroyed(EntityIdentifier entity)
	{
	}

	void Allocator::RemoveDestroyedEntities()
	{
	}
}

