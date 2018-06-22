#pragma once

#ifdef ECS_EXPORTS  
#define ECS_API __declspec(dllexport)   
#else  
#define ECS_API __declspec(dllimport)   
#endif  

#define MAX_COMPONENTS 32