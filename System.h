#pragma once

namespace ECS {
	class ECS;

	class System
	{
	public:
		ECS * ecs = nullptr;
		virtual void Init() {};
	};
}


