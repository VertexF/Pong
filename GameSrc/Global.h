#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "GameSession.h"
#include "Singleton.h"

namespace game 
{
#define GAME_SESSION (Singleton<GameSession>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
