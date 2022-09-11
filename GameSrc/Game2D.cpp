#include "PreComp.h"
#include "Game2D.h"

#include "GameState.h"
#include "LoadingState.h"
#include "InitState.h"
#include "MainState.h"
#include "GlobalState.h"
#include "Global.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <cmath>

namespace game
{
    Game2D::Game2D() : Layer("Game")
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _posX = 0.f;
        _posY = 0.f;

        GAME_STATE.pushState(std::make_shared<InitState>(InitState()));
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);
    }

    void Game2D::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void Game2D::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        switch (GAME_STATE.getCurrentState())
        {
        case CLASS_STATE::INIT_STATE:
            GAME_STATE.switchState(std::make_shared<LoadingState>(LoadingState()));
            break;
        case CLASS_STATE::LOADING_STATE:
            GAME_STATE.switchState(std::make_shared<MainState>(MainState()));
            break;
        case CLASS_STATE::MAIN_STATE:
            break;
        }

        GAME_STATE.update();

        _cameraController->onUpdate(timeStep);

        Tempest::RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
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
