#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "Singleton.h"
#include "ResourceManager.h"

namespace game 
{
#define RESOURCE_MANAGER (Singleton<ResourceManager>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
