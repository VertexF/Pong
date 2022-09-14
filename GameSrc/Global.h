#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "LevelTheme.h"
#include "GameSession.h"
#include "Singleton.h"

namespace game 
{
#define GAME_SESSION (Singleton<GameSession>::getInstance())
#define GAME_THEME (Singleton<LevelTheme>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
