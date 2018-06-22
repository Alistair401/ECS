#pragma once

#include "ECS.h"
#include "Component.h"

#include <bitset>

namespace ECS {
	class ECS_API Entity {
	public:
		bool IsAlive();
		void Destroy();

		template<typename T, typename... TArgs>
		void AddComponent(TArgs&&... args) {

		}

		template<typename T>
		bool HasComponent() {
			return false;
		}
	private:
		bool alive = true;
	};
}
