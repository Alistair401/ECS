#pragma once

#include "Util.h"

namespace ECS {
	class Component
	{
	public:
		virtual ~Component() {}
	};

	inline ComponentID GenerateComponentIdentifier() {
		static ComponentID last_identifier{ 0 };
		last_identifier++;
		assert(last_identifier < MAX_COMPONENTS);
		return last_identifier;
	}

	template<typename ComponentType>
	inline ComponentID GetComponentIdentifier() {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must inherit from the Component class");

		static ComponentID type_id{ GenerateComponentIdentifier() };
		return type_id;
	}
}
