#ifndef INFINITE_STATE_HDR
#define INFINITE_STATE_HDR

#include "GameState.h"
#include "GlobalState.h"

namespace game 
{
    class InfiniteState : public GameState 
    {
        public: 
            InfiniteState();
            virtual ~InfiniteState() = default;

            virtual void onResume() override {}

            virtual void update() override;
    };
}

#endif // !INFINITE_STATE_HDR
