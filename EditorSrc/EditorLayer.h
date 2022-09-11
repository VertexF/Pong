#ifndef EDITOR_LAYER_HDR
#define EDITOR_LAYER_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"

namespace Tempest
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        virtual ~EditorLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate(TimeStep timeStep) override;
        virtual void onEvent(Event& e) override;
        virtual void onImGuiRender() override;
        virtual bool isFinished() const override;
    private:
        bool onKeyPressed(PressedKeyEvent& e);
        bool onKeyReleased(ReleasedKeyEvent& e);
    private:
        scope<OrthographicalCameraController> _cameraController;
        scope<TextRenderer> _testText;

        glm::vec4 _squareColour;
        ref<Texture2D> _backgroundTexture;
        ref<Texture2D> _transCheck;
        ref<Framebuffer> _framebuffer;

        uint32_t _spellSoundBuffer = 0;
        uint32_t _magicFailSoundBuffer = 0;

        ref<SoundDevice> _soundDevice;
        ref<SoundBuffer> _soundBuffer;
        ref<SoundSource> _mySource;

        glm::vec2 _viewportSize;

        std::vector<float> _xPos;
        std::vector<float> _yPos;

        float _posX;
        float _posY;

        bool _viewportFocused = false;
        bool _viewportHoved = false;
    };
}

#endif //!EDITOR_LAYER_HDR