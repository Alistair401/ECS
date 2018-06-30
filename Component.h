#pragma once

#include "Util.h"

namespace ECS {
	class Component
	{
	public:
		virtual ~Component() {}
	};

	inline ComponentIdentifier GenerateComponentIdentifier() {
		static ComponentIdentifier last_identifier{ 0 };
		last_identifier++;
		assert(last_identifier < MAX_COMPONENTS);
		return last_identifier;
	}

	template<typename ComponentType>
	inline ComponentIdentifier GetComponentIdentifier() {
		static_assert(std::is_base_of<Component, ComponentType>::value, "ComponentType must inherit from the Component class");

		static ComponentIdentifier type_id{ GenerateComponentIdentifier() };
		return type_id;
	}
}
