#ifndef GLOBAL_HDR
#define GLOBAL_HDR

#include "GameSession.h"
#include "MarioGame.h"
#include "Singleton.h"

namespace game 
{
#define GAME_SESSION (Singleton<GameSession>::getInstance())
#define GAME_STATE (Singleton<MarioGame>::getInstance())

    void creatsGlobals();

    void destroyGlobals();
}

#endif // !GLOBAL_HDR
