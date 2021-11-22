#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace 
{
    const uint32_t MAP_WIDTH = 24;
    const char* TILE_MAP = 
        "WWWWWWWWWWWWWWWWWWWWWWWW"
        "WWWWWWWWWWWWWWWWWWWWWWWW"
        "WWWWWDDDDDDDDDDDDDWWWWWW"
        "WWWWDDDDDDDDDDDDDDDWWWWW"
        "WWWDDDDDDDDDDDDDDDDDWWWW"
        "WWWWDDDDDDDDDDDDDDDDWWWW"
        "WWWWWWDDDDDDDDDDDDDDDWWW"
        "WWWWWWWDDDDDDDDDDDDDWWWW"
        "WWWWDDDDDDDDDDDDDDDDDWWW"
        "WWWWWWDDDWWDDDDDDDDDDWWW"
        "WWWWWWWDDWWDDDDDDDDDDWWW"
        "WWWWWWWWDDWWWDDDDWWWWWWW"
        "WWWWWWWWDDDDDDDDDDWWWWWW"
        "WWWWWWWWWDDDDDDDDDDWWWWW"
        "WWWWWWWWWDDDDDDDDWWWWWWW"
        "WWWWWWWWWWWDDDDWWWWWWWWW"
        "WWWWWWWWWWWWWWWWWWWWWWWW";
}

namespace game
{
    Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
    {
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _testText = std::make_unique<Tempest::TextRenderer>(128.f);

        _soundDevice = Tempest::SoundDevice::create();
        _soundBuffer = Tempest::SoundBuffer::create();
        _mySource = std::make_shared<Tempest::SoundSource>();

        _spriteSheet = Tempest::Texture2D::create("Assets/Textures/RPGpack_sheet_2X.png");

        _grassTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheet, { 0, 19 }, { 128, 128 });
        _textureMap['D'] = Tempest::SubTexture2D::createFromCoords(_spriteSheet, { 6, 11 }, { 128, 128 });
        _textureMap['W'] = Tempest::SubTexture2D::createFromCoords(_spriteSheet, { 11, 11 }, { 128, 128 });

        _mapWidth = MAP_WIDTH;
        _mapHieght = strlen(TILE_MAP) / MAP_WIDTH;
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(10.f);

        _spellSoundBuffer = _soundBuffer->addSoundEffect("Assets/Audio/spell.wav");
        _magicFailSoundBuffer = _soundBuffer->addSoundEffect("Assets/Audio/magicfail.wav");
    }

    void Game2D::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Game2D::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->onUpdate(timeStep);
        //_vehicle->onUpdate(timeStep);
        Tempest::Renderer2D::resetStats();

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        for (uint32_t y = 0; y < _mapHieght; y++) 
        {
            for (uint32_t x = 0; x < _mapWidth; x++) 
            {
                char key = TILE_MAP[x + y * _mapWidth];
                Tempest::ref<Tempest::SubTexture2D> texture;
                if (_textureMap.find(key) != _textureMap.end()) 
                {
                    texture = _textureMap[key];
                }
                else 
                {
                    texture = _grassTexture;
                }

                Tempest::Renderer2D::drawQuad({ x - _mapWidth / 2.f, y - _mapHieght / 2.f, 0.5f }, { 1.f, 1.f }, texture);
            }
        }

        _testText->displayText({ -2.f, 4.0f }, { 1.f, 1.f }, _squareColour, "Tech Demo!");
        Tempest::Renderer2D::endScene();
    }

    void Game2D::onEvent(Tempest::Event& e)
    {
        _cameraController->onEvent(e);

        Tempest::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&Game2D::onKeyPressed, this, std::placeholders::_1));
        dispatcher.dispatch<Tempest::ReleasedKeyEvent>(std::bind(&Game2D::onKeyReleased, this, std::placeholders::_1));
    }

    void Game2D::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();
        ImGui::Begin("Settings");

        auto stats = Tempest::Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getTotalVertices());
        ImGui::Text("Indices: %d", stats.getTotalIndices());

        ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

        ImGui::End();
    }

    bool Game2D::onKeyPressed(Tempest::PressedKeyEvent& e)
    {
        switch (e.getKeyCode()) 
        {
        case TEMP_KEY_1:
            _mySource->play(_spellSoundBuffer);
            break;
        case TEMP_KEY_2:
            _mySource->play(_magicFailSoundBuffer);
            break;
        }

        return false;
    }

    bool Game2D::onKeyReleased(Tempest::ReleasedKeyEvent& e) 
    {
        return false;
    }

}
