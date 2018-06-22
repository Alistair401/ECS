#pragma once

#include "ECS.h"

using TypeIdentifier = size_t;

inline TypeIdentifier GenerateTypeIdentifier() {
	static TypeIdentifier last_identifier{ 0 };
	return last_identifier++;
}

namespace ECS {
	template<typename T>
	inline TypeIdentifier GetTypeIdentifier() {
		static TypeIdentifier type_id{ GenerateTypeIdentifier() };
		return type_id;
	}
}
