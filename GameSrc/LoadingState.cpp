#include "LoadingState.h"

#include "Global.h"
#include "MainState.h"
#include <memory>

namespace game 
{
    LoadingState::LoadingState()
    {
        _state = CLASS_STATE::LOADING_STATE;
        TEMPEST_INFO("Entered Loading state.");
    }

    void LoadingState::update() 
    {
        TEMPEST_INFO("Loading assets");
        TEMPEST_INFO("Building up the resource manager");
        TEMPEST_INFO("Switching to MainState");
    }
}