#ifndef GAME_STATE_HDR
#define GAME_STATE_HDR

#include <memory>

#include <Tempest.h>
#include "GlobalState.h"

namespace game 
{
    class GameState 
    {
    protected:
        CLASS_STATE _state;
    public:
        GameState() 
        {
            TEMPEST_INFO("Constructing GameState.");
        }

        virtual ~GameState() 
        {
            TEMPEST_INFO("Deleting GameState from memory.");
        }

        virtual void onResume() {}

        virtual void update() = 0;

        CLASS_STATE getCurrentState() const { return _state; }
    };
}

#endif // !GAME_STATE_HDR
