#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "LevelTheme.h"
#include "GameSession.h"
#include "ResourceManager.h"
#include "Singleton.h"

namespace game 
{
#define RESOURCE_MANAGER (Singleton<ResourceManager>::getInstance());
#define GET_RESOURCE_GROUP(name) (Singleton<ResourceManager>::getInstance().getResourceGroup(name))
#define DEFAULT_RESOURCE_GROUP_NAME "default"
#define DEFAULT_RESOURCE_GROUP (GET_RESOURCE_GROUP(DEFAULT_RESOURCE_GROUP_NAME))

// Note: Do not use these macros within entity classes unless the resources should not be overridden
#define GET_BACKGROUND(name) (DEFAULT_RESOURCE_GROUP->getBackground(name))

#define GAME_SESSION (Singleton<GameSession>::getInstance())
#define GAME_THEME (Singleton<LevelTheme>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
