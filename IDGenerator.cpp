#include "stdafx.h"
#include "IDGenerator.h"

#include <assert.h>

unsigned int ECS::IDGenerator::Generate()
{
	if (free_ids.size() > 0) {
		unsigned int id = free_ids.back();
		free_ids.pop_back();
		return id;
	}

	assert(next_id != upper_limit);

	return next_id++;
}

void ECS::IDGenerator::Free(unsigned int ID)
{
	free_ids.push_back(ID);
}
