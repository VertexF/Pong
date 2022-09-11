#include "InitState.h"
#include <Tempest.h>

namespace game 
{
    InitState::InitState() 
    {
        _state = CLASS_STATE::INIT_STATE;
        TEMPEST_INFO("Entered Init state.");
    }

    void InitState::update() 
    {
        TEMPEST_INFO("In Init state.");
    }
}