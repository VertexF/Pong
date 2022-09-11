#include "MarioGame.h"

namespace game 
{
    MarioGame::MarioGame() : _frameCount(0)
    {
    }

    void MarioGame::pushState(std::shared_ptr<GameState> newState)
    {
        _gameStates.emplace_back(newState);
    }

    void MarioGame::popState() 
    {
        _gameStates.pop_back();
        if (_gameStates.empty() == false) 
        {
            _gameStates.back()->onResume();
        }
    }

    void MarioGame::switchState(std::shared_ptr<GameState> newState) 
    {
        popState();
        pushState(newState);
    }

    void MarioGame::quit() 
    {
        while (isRunning()) 
        {
            popState();
        }
    }

    void MarioGame::update() 
    {
        if (isRunning() == false)
        {
            return;
        }

        _gameStates.back()->update();

        //Note: Note usre if we need to worry about this at all.
        //if (stateStack.back()->throttle)
        //{
        //    FPS_MANAGER.update();
        //}

        //TODO: Needs clamping to a value range.
        _frameCount++;
    }
}