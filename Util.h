#pragma once

#include <bitset>


namespace ECS {
	constexpr size_t MAX_COMPONENTS = 32;

	using ComponentBitset = std::bitset<MAX_COMPONENTS>;

	using EntityIdentifier = unsigned int;
	using ComponentIdentifier = unsigned int;

	inline ComponentIdentifier GenerateComponentIdentifier() {
		static ComponentIdentifier last_identifier{ 0 };
		return last_identifier++;
	}

	template<typename EntityType>
	inline ComponentIdentifier GetComponentIdentifier() {
		static ComponentIdentifier type_id{ GenerateComponentIdentifier() };
		return type_id;
	}
}
