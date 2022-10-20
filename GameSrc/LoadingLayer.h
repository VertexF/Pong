#ifndef LOADING_LAYER_HDR
#define LOADING_LAYER_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"

namespace game
{
    class LoadingLayer : public Tempest::Layer
    {
    public:
        LoadingLayer();
        virtual ~LoadingLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(Tempest::TimeStep timeStep) override;
        virtual void onEvent(Tempest::Event& e) override;
        virtual void onImGuiRender() override;
        virtual bool isFinished() const override;
    private:
        bool onKeyPressed(Tempest::PressedKeyEvent& e);
        bool onKeyReleased(Tempest::ReleasedKeyEvent& e);
    private:
        Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;

        float _posX;
        float _posY;

        bool finished = false;
    };
}

#endif //!LOADING_LAYER_HDR