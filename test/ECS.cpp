#include "stdafx.h"
#include "../ECS.h"
#include "../EventSubscriber.h"

TEST(ECS, SystemsAreRegistered) {
	struct DummyEvent {
		int payload = 401;
	};

	struct DummySystem : ECS::System {
		void Init() override {
			ecs->Notify(DummyEvent{});
		}
	};

	struct DummySubscriber : ECS::EventSubscriber<DummyEvent> {
		int test_data = 123;
		void OnEvent(const DummyEvent& event) {
			test_data = event.payload;
		}
	};

	DummySubscriber* dummy_sub = new DummySubscriber();

	ECS::ECS ecs;
	ecs.Subscribe(dummy_sub);
	ecs.AddSystem<DummySystem>();

	ASSERT_TRUE(dummy_sub->test_data == 401);
}

TEST(ECS, EventsAreEmitted) {
	struct DummyEvent {
		int payload = 401;
	};
	struct DummySubscriber : ECS::EventSubscriber<DummyEvent> {
		int test_data = 123;
		void OnEvent(const DummyEvent& event) {
			test_data = event.payload;
		}
	};

	DummySubscriber* dummy_sub = new DummySubscriber();
	DummyEvent dummy_event{};
	ECS::ECS ecs;
	ecs.Subscribe(dummy_sub);
	ecs.Notify(dummy_event);
	
	ASSERT_TRUE(dummy_sub->test_data == dummy_event.payload);
}

TEST(ECS, SystemsAreUpdated) {
	struct DummyEvent {
		int payload = 401;
	};

	struct DummySystem : ECS::System {
		void Update(float dt) override {
			ecs->Notify(DummyEvent{});
		}
	};

	struct DummySubscriber : ECS::EventSubscriber<DummyEvent> {
		int test_data = 123;
		void OnEvent(const DummyEvent& event) {
			test_data = event.payload;
		}
	};

	DummySubscriber* dummy_sub = new DummySubscriber();

	ECS::ECS ecs;
	ecs.Subscribe(dummy_sub);
	ecs.AddSystem<DummySystem>();
	ecs.Update(0.1);

	ASSERT_TRUE(dummy_sub->test_data == 401);
}