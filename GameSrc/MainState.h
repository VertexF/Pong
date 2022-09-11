#ifndef MAIN_STATE_HDR
#define MAIN_STATE_HDR

#include "GameState.h"
#include "GlobalState.h"
#include <Tempest.h>

namespace game 
{
    class MainState : public GameState
    {
    public:
        MainState() 
        {
            _state = CLASS_STATE::MAIN_STATE;
            TEMPEST_INFO("Entered Main state.");
        }

        virtual ~MainState() 
        {
            TEMPEST_INFO("Entered leaving main state.");
        }

        virtual void onResume() override {}

        virtual void update() override;
    };
}

#endif // !MAIN_STATE_HDR
