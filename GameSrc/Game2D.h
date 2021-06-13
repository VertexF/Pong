#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"

#include "RtAudio.h"
#include "TextTest.h"

namespace game
{
    class Game2D : public Tempest::Layer
    {
    public:
        Game2D();
        virtual ~Game2D() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(Tempest::TimeStep timeStep) override;
        virtual void onEvent(Tempest::Event& e) override;
        virtual void onImGuiRender() override;
    private:
        glm::vec4 _squareColour;

        Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;
        Tempest::scope<::RtAudio> _rtAudio;

        Tempest::scope<TextTest> _testText;
    };
}

#endif //!GAME_2D_HDR