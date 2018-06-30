#pragma once

#include <bitset>

#include <assert.h>

namespace ECS {
	constexpr size_t MAX_COMPONENTS = 32;
	constexpr size_t MAX_ENTITIES = 100;

	using ComponentBitset = std::bitset<MAX_COMPONENTS>;

	using EntityIdentifier = unsigned int;
	using ComponentIdentifier = unsigned int;
}
