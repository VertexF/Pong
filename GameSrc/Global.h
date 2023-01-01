#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "Singleton.h"
#include "ResourceManager.h"
#include "EntityManager.h"

namespace game 
{
#define RESOURCE_MANAGER (Singleton<ResourceManager>::getInstance())
#define ENTITY_MANAGER (Singleton<EntityManager>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
