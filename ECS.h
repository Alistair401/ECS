#pragma once

#ifdef ECS_EXPORTS  
	#define ECS_API __declspec(dllexport)   
#else  
	#define ECS_API __declspec(dllimport)   
#endif  

namespace ECS
{
	class ECS_API Entity {
	};
}
