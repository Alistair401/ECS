#include "pch.h"
#include "../Component.h"

TEST(Component, ComponentTypesHaveUniqueIDs) {
	struct ComponentA : ECS::Component {};
	struct ComponentB : ECS::Component {};
	ASSERT_TRUE(ECS::GetTypeIdentifier<ComponentA>() != ECS::GetTypeIdentifier<ComponentB>());
}
