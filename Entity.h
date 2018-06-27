#pragma once

#include "Util.h"


namespace ECS {
	class ECS;

	class Entity
	{
	public:
		EntityIdentifier id;
		ECS* ecs;

		template <typename ComponentType, typename... TArgs>
		ComponentType& AddComponent(TArgs&&... args) {

		}

		template <typename ComponentType>
		ComponentType& GetComponent() {

		}

		template <typename ComponentType>
		bool HasComponent() {

		}
	};
}


