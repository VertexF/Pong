#ifndef LOADING_STATE_HDR
#define LOADING_STATE_HDR

#include "GameState.h"
#include "GlobalState.h"

namespace game 
{
    class LoadingState : public GameState
    {
    public:
        LoadingState();
        virtual ~LoadingState() = default;

        virtual void onResume() override {}

        virtual void update() override;
    };
}

#endif // !LOADING_STATE_HDR
