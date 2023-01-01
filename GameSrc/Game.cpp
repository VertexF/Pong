#include <iostream>
#include <Tempest.h>

#include "Tempest/Core/EntryPoint.h"

#include "Game2D.h"
#include "LoadingLayer.h"
#include "MenuLayer.h"

namespace game
{
    //The client uses the application as a template to create the game.
    class Game : public Tempest::Application
    {
    public:
        Game()
        {
            //TODO: Workout away to add new things to the game stack, when an old layer is deleted.
            //Instead of adding them all to the stack all at once, might save RAM and startup time.
            pushGameLayer(new Game2D());
            //pushGameLayer(new LoadingLayer());
            //pushGameLayer(new MenuLayer());
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