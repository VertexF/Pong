#ifndef MARIO_GAME_HDR
#define MARIO_GAME_HDR

#include <list>
#include <memory>

#include "GameState.h"

namespace game 
{
    //Mario games owns all the states.
    //Each state is a class that contains a game play phrase, loading or otherwise.
    //Each stage is a unique point that is inside a templated linked list. No idea if it's possible to update the state like that but it would solve the problem
    class MarioGame 
    {
    public:
        MarioGame();
        //We are using share_ptr so we should leave deleting objects up to them.
        ~MarioGame() = default;

        void pushState(std::shared_ptr<GameState> newState);
        void popState();

        void switchState(std::shared_ptr<GameState> newState);

        int getFramecount() const { return _frameCount; }
        bool isRunning() const { return (_gameStates.empty() == false); }

        void quit();

        void update();

        CLASS_STATE getCurrentState() const { return _gameStates.back()->getCurrentState(); }

    private:
        std::list<std::shared_ptr<GameState>> _gameStates;

        //Used for effects more than anything can be removed or clamped to avoid interger overflow.
        int _frameCount;
    };
}

#endif // !MARIO_GAME_HDR
