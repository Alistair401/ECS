#include "stdafx.h"
#include "../ECS.h"

TEST(ECS, SystemsAreRegistered) {
	struct DummySystem : ECS::System {
		void Init() override {

		}
	};
	ECS::ECS ecs;
	ecs.AddSystem<DummySystem>();
}

TEST(ECS, EventsAreEmitted) {
	struct DummyEvent : ECS::Event {

	};
}