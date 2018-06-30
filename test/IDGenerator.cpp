#include "stdafx.h"
#include "../IDGenerator.h"

TEST(IDGenerator, IDsAreUnique) {
	ECS::IDGenerator gen{2};

	ASSERT_TRUE(gen.Generate() != gen.Generate());
}

TEST(IDGenerator, IDsAreReused) {
	ECS::IDGenerator gen{ 2 };

	unsigned int id_a = gen.Generate();
	unsigned int id_b = gen.Generate();
	gen.Free(id_b);
	unsigned int id_c = gen.Generate();

	ASSERT_TRUE(id_b == id_c);
}

TEST(IDGenerator, ExceedingIDLimitThrows) {
	unsigned int limit = 2;
	ECS::IDGenerator gen{ limit };

	for (unsigned int i = 0; i < limit; i++)
	{
		gen.Generate();
	}

	ASSERT_DEATH(gen.Generate(), "");
}
