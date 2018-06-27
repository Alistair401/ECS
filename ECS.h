#pragma once

#include "Util.h"
#include "Allocator.h"
#include "Entity.h"

#include <type_traits>

namespace ECS {
	class ECS
	{
	public:
		ECS() {
			allocator = new Allocator();
		}

		void Update(float dt) {

		}

		template <typename EntityType>
		EntityType& CreateEntity() {
			static_assert(std::is_base_of<Entity, EntityType>::value, "EntityType must inherit from the Entity class");

			EntityType* entity = new EntityType();
			entity->ecs = this;
			entity->id = allocator->CreateEntity();

			return *entity;
		}

	private:
		Allocator * allocator;
	};
}
