#include "pch.h"
#include "../Entity.h"

struct EmptyEntity : ECS::Entity {};

EmptyEntity* InstantiateEmptyEntity() {
	return new EmptyEntity();
}

TEST(Entity, IsAlive) {
	EmptyEntity* e = InstantiateEmptyEntity();
	ASSERT_TRUE(e->IsAlive());
}

TEST(Entity, GetsDestroyed) {
	EmptyEntity* e = InstantiateEmptyEntity();
	e->Destroy();
	ASSERT_TRUE(!e->IsAlive());
}

TEST(Entity, ComponentsAreAddedToEntity) {
	EmptyEntity* e = InstantiateEmptyEntity();
	struct DummyComponent : ECS::Component {

	};

	ASSERT_TRUE(!e->HasComponent<DummyComponent>());
	e->AddComponent<DummyComponent>();
	ASSERT_TRUE(e->HasComponent<DummyComponent>());
}

