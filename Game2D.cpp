#include "PreComp.h"
#include "Game2D.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

namespace 
{
    const int MAP_WIDTH = 64;
}

namespace game
{
    Game2D::Game2D() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _testText = std::make_unique<Tempest::TextRenderer>(128.f);

        _soundDevice = Tempest::SoundDevice::create();
        _soundBuffer = Tempest::SoundBuffer::create();
        _mySource = std::make_shared<Tempest::SoundSource>();

        _backgroundTexture = Tempest::Texture2D::create("Assets/Textures/Checkerboard.png");
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);

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

        Tempest::Renderer2D::resetStats();

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        Tempest::Renderer2D::drawQuad({ 1.f, 0.f, 0.5f }, { 30.f, 30.f }, _backgroundTexture, 20.f, { 0.4f, 0.8f, 0.8f, 1.f });

        _testText->displayText({ -1.f, -3.f, 0.1f}, { 1.f, 1.f }, _squareColour, "The Game!");

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
