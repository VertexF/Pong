#include "PreComp.h"
#include "Game2D.h"

#include "Global.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <cmath>
#include <vector>

namespace game
{
    Game2D::Game2D() : Layer("Game")
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _posX = 0.f;
        _posY = 0.f;
        //_frameCount = 0;
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();
        _frameCount = 0;
        _levelTheme = RESOURCE_MANAGER.getLevelTheme("smb3_ice_cave_theme");
        _cameraController->setZoomLevel(4.5f);
    }

    void Game2D::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Game2D::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->onUpdate(timeStep);

        Tempest::RendererCommands::setClearColour({ 0.4f, 0.4f, 0.4f, 1.f });
        Tempest::RendererCommands::clear();

        if (Tempest::Input::isKeyPressed(TEMP_KEY_W)) 
        {
            _posY += 1.5f * timeStep;
        }

        if (Tempest::Input::isKeyPressed(TEMP_KEY_S))
        {
            _posY -= 1.5f * timeStep;
        }

        if (Tempest::Input::isKeyPressed(TEMP_KEY_A))
        {
            _posX -= 1.5f * timeStep;
        }

        if (Tempest::Input::isKeyPressed(TEMP_KEY_D))
        {
            _posX += 1.5f * timeStep;
        }

        _cameraController->setCameraPosition({ _posX, _posY, 0.0f });

        Tempest::Renderer2D::resetStats();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        Tempest::Renderer2D::drawQuad({ 0, 0 }, { 16, 9 }, _levelTheme->getBackground(0)->getAnimation()->getFrame(_frameCount));
        Tempest::Renderer2D::drawQuad({ 16, 0 }, { 16, 9 }, _levelTheme->getBackground(0)->getAnimation()->getFrame(_frameCount));
        Tempest::Renderer2D::drawQuad({ 32, 0 }, { 16, 9 }, _levelTheme->getBackground(0)->getAnimation()->getFrame(_frameCount));

        Tempest::Renderer2D::endScene();

        if (_frameCount >= 40) 
        {
            _frameCount = 0;
        }
        _frameCount++;
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
    }

    bool Game2D::isFinished() const
    {
        return false;
    }

    bool Game2D::onKeyPressed(Tempest::PressedKeyEvent& e)
    {
        return false;
    }

    bool Game2D::onKeyReleased(Tempest::ReleasedKeyEvent& e) 
    {
        return false;
    }
}
