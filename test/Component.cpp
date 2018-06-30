#include "stdafx.h"

#include "../Component.h"

TEST(Component, ComponentTypesHaveUniqueIDs) {
	struct ComponentA : ECS::Component {};
	struct ComponentB : ECS::Component {};
	ASSERT_TRUE(ECS::GetComponentIdentifier<ComponentA>() != ECS::GetComponentIdentifier<ComponentB>());
}
