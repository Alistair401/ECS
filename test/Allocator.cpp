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
	ECS::EntityIdentifier entity = allocator.CreateEntity();
	ASSERT_TRUE(!allocator.HasComponent<EmptyComponent>(entity));
	allocator.AddComponent<EmptyComponent>(entity);
	ASSERT_TRUE(allocator.HasComponent<EmptyComponent>(entity));
}

TEST(Allocator, ComponentsAreAllocated) {

	struct DummyComponent : ECS::Component {
		int test_data = 123;
	};

	ECS::Allocator allocator;
	ECS::EntityIdentifier entity = allocator.CreateEntity();

	DummyComponent& component_instance = allocator.AddComponent<DummyComponent>(entity);

	ASSERT_TRUE(component_instance.test_data == 123);
}