#pragma once

#include <vector>

namespace ECS {
	class IDGenerator
	{
	public:
		IDGenerator(unsigned int upper_limit) :upper_limit(upper_limit) {};
		unsigned int Generate();
		void Free(unsigned int ID);
	private:
		const unsigned int upper_limit;
		unsigned int next_id = 0;
		std::vector<unsigned int> free_ids;
	};
}
