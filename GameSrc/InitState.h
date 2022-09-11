#ifndef INIT_STATE_HDR
#define INIT_STATE_HDR

#include "GameState.h"
#include "GlobalState.h"

namespace game 
{
    class InitState : public GameState 
    {
    public:
        InitState();
        virtual ~InitState() = default;

        void update();
    };
}

#endif // !INIT_STATE_HDR
