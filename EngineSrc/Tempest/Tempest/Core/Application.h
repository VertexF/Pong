#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include "PreComp.h"
#include "Window.h"
#include "Tempest/Events/Event.h"
#include "Tempest/Events/ApplicationEvents.h"
#include "LayerStack.h"
#include "Tempest/ImGui/ImGUILayer.h"

#include "TimeStep.h"

namespace Tempest
{
    class Layer;

    //This is the main coordinator class.
    class Application
    {
    public:
        Application(const std::string& title = "Tempest Engine");
        virtual ~Application();

        void onEvent(Event &e);
        void run();

        void pushLayer(Layer *layer);
        void pushOverlay(Layer *layer);

        inline static Application& get() { return *_instance; }
        inline Window& getWindow() const { return *_window;  }

        ImGuiLayer* getImGuiLayer();

        void close();
    private:
        bool onWindowClosed(WindowClosedEvent &closed);
        bool onWindowResize(WindowResizeEvent& resized);
    private:
        bool _running;
        bool _minimized = false;
        ImGuiLayer* _imGuiLayer;
        std::unique_ptr<Window> _window;
        LayerStack _layerStack;

        float _lastFrameTime  = 0.f;
        static Application* _instance;
    };

    //To be defined in the client. This is how you use the shared library.
    Application* createApplication();
}

#endif // TEST_HDR
