#include <iostream>
#include <Tempest.h>

#include "Tempest/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Tempest
{
    //The client uses the application as a template to create the game.
    class TempestEditor : public Application
    {
    public:
        TempestEditor() : Application("Tempest Editor")
        {
            pushLayer(new EditorLayer());
        }

        ~TempestEditor() {}
    };

    //We kick start the engine by using our client class that is 
    //inherited from the the engine.
    Application* createApplication()
    {
        return new TempestEditor();
    }
}