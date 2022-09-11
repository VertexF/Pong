#include <iostream>
#include <Tempest.h>

#include "Tempest/Core/EntryPoint.h"

#include "Game2D.h"
#include "LoadingLayer.h"

namespace game
{
    //The client uses the application as a template to create the game.
    class Game : public Tempest::Application
    {
    public:
        Game()
        {
            pushGameLayer(new Game2D());
            pushGameLayer(new LoadingLayer());
        }

        virtual ~Game() = default;
    };
}

//We kick start the engine by using our client class that is 
//inherited from the the engine.
Tempest::Application* Tempest::createApplication() 
{
    return new game::Game();
}