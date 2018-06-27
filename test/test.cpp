#include "stdafx.h"
#include "../ECS.h"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Entity, IsInstantiated) {
	struct EmptyEntity : ECS::Entity {

	};

	ECS::ECS* ecs = new ECS::ECS();
	EmptyEntity& entity_a = ecs->CreateEntity<EmptyEntity>();
	EmptyEntity& entity_b = ecs->CreateEntity<EmptyEntity>();

	ASSERT_TRUE(entity_a.id != entity_b.id);
}
