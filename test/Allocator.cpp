#include "stdafx.h"

#include "../Allocator.h"

TEST(Allocator, EntitiesAreAllocated) {
	ECS::Allocator allocator;

	for (size_t i = 0; i < ECS::MAX_ENTITIES; i++)
	{
		allocator.CreateEntity();
	}
}

TEST(Allocator, ExceedingEntityLimitThrows) {
	ECS::Allocator allocator;

	for (size_t i = 0; i < ECS::MAX_ENTITIES; i++)
	{
		allocator.CreateEntity();
	}

	ASSERT_DEATH(allocator.CreateEntity(), "");
}

TEST(Allocator, ComponentMaskIsUpdated) {
	struct EmptyComponent : ECS::Component {

	};

	ECS::Allocator allocator;
	ECS::EntityID entity = allocator.CreateEntity();
	ASSERT_TRUE(!allocator.HasComponent<EmptyComponent>(entity));
	allocator.AddComponent<EmptyComponent>(entity);
	ASSERT_TRUE(allocator.HasComponent<EmptyComponent>(entity));
}

TEST(Allocator, ComponentsAreAllocated) {

	struct DummyComponent : ECS::Component {
		int test_data = 123;
	};

	ECS::Allocator allocator;
	ECS::EntityID entity = allocator.CreateEntity();

	DummyComponent& component_instance = allocator.AddComponent<DummyComponent>(entity);

	ASSERT_TRUE(component_instance.test_data == 123);
}

TEST(Allocator, ComponentsAreRetrieved) {
	struct DummyComponent : ECS::Component {
		int test_data = 123;
	};

	ECS::Allocator allocator;
	ECS::EntityID entity = allocator.CreateEntity();

	DummyComponent& component_instance = allocator.AddComponent<DummyComponent>(entity);

	component_instance.test_data = 401;

	component_instance = allocator.GetComponent<DummyComponent>(entity);

	ASSERT_TRUE(component_instance.test_data == 401);
}

TEST(Allocator, CanActOnComponents) {
	struct DummyComponent : ECS::Component {
		int test_data = 123;
	};

	ECS::Allocator allocator;
	ECS::EntityID entity = allocator.CreateEntity();
	DummyComponent& component = allocator.AddComponent<DummyComponent>(entity);

	allocator.Each<DummyComponent>([](ECS::EntityID entity, DummyComponent& c) {
		c.test_data = 401;
	});

	ASSERT_TRUE(component.test_data == 401);
}
