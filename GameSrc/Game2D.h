#ifndef GAME_2D_HDR
#define GAME_2D_HDR

#include <Tempest.h>
#include <ImGui.h>

#include "Tempest/Events/Event.h"
#include "Tempest/Events/KeyEvents.h"

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
        bool onKeyPressed(Tempest::PressedKeyEvent& e);
        bool onKeyReleased(Tempest::ReleasedKeyEvent& e);
    private:
        glm::vec4 _squareColour;

        uint32_t _mapWidth;
        uint32_t _mapHieght;

        Tempest::scope<Tempest::OrthographicalCameraController> _cameraController;
        Tempest::scope<Tempest::TextRenderer> _testText;

        Tempest::ref<Tempest::Texture2D> _spriteSheet;
        Tempest::ref<Tempest::SubTexture2D> _grassTexture;

        uint32_t _spellSoundBuffer = 0;
        uint32_t _magicFailSoundBuffer = 0;

        Tempest::ref<Tempest::SoundDevice> _soundDevice;
        Tempest::ref<Tempest::SoundBuffer> _soundBuffer;
        Tempest::ref<Tempest::SoundSource> _mySource;

        std::unordered_map<char, Tempest::ref<Tempest::SubTexture2D>> _textureMap;
    };
}

#endif //!GAME_2D_HDR