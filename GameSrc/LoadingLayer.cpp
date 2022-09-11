#include "PreComp.h"
#include "LoadingLayer.h"

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
    LoadingLayer::LoadingLayer() : Layer("Loading")
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _posX = 0.f;
        _posY = 0.f;

        finished = false;
    }

    void LoadingLayer::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);
    }

    void LoadingLayer::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void LoadingLayer::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->onUpdate(timeStep);

        Tempest::RendererCommands::setClearColour({ 0.9f, 0.9f, 0.2f, 1.f });
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

        if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE))
        {
            finished = true;
        }

        _cameraController->setCameraPosition({ _posX, _posY, 0.0f });

        Tempest::Renderer2D::resetStats();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());
        Tempest::Renderer2D::endScene();
    }

    void LoadingLayer::onEvent(Tempest::Event& e)
    {
        _cameraController->onEvent(e);

        Tempest::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&LoadingLayer::onKeyPressed, this, std::placeholders::_1));
        dispatcher.dispatch<Tempest::ReleasedKeyEvent>(std::bind(&LoadingLayer::onKeyReleased, this, std::placeholders::_1));
    }

    void LoadingLayer::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    bool LoadingLayer::isFinished() const
    {
        return finished;
    }

    bool LoadingLayer::onKeyPressed(Tempest::PressedKeyEvent& e)
    {
        return false;
    }

    bool LoadingLayer::onKeyReleased(Tempest::ReleasedKeyEvent& e) 
    {
        return false;
    }
}
