#include "PreComp.h"
#include "MenuLayer.h"

#include "Global.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <cmath>

namespace game
{
    MenuLayer::MenuLayer() : Layer("Menu")
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<Tempest::OrthographicalCameraController>(1280.f / 720.f);

        _posX = 0.f;
        _posY = 0.f;

        finished = false;
    }

    void MenuLayer::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);
    }

    void MenuLayer::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void MenuLayer::onUpdate(Tempest::TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->onUpdate(timeStep);

        Tempest::RendererCommands::setClearColour({ 0.9f, 0.9f, 0.2f, 1.f });
        Tempest::RendererCommands::clear();

        if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE))
        {
            finished = true;
        }

        _cameraController->setCameraPosition({ _posX, _posY, 0.0f });

        Tempest::Renderer2D::resetStats();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());
        Tempest::Renderer2D::endScene();

        finished = true;
    }

    void MenuLayer::onEvent(Tempest::Event& e)
    {
        _cameraController->onEvent(e);

        Tempest::EventDispatcher dispatcher(e);
        dispatcher.dispatch<Tempest::PressedKeyEvent>(std::bind(&MenuLayer::onKeyPressed, this, std::placeholders::_1));
        dispatcher.dispatch<Tempest::ReleasedKeyEvent>(std::bind(&MenuLayer::onKeyReleased, this, std::placeholders::_1));
    }

    void MenuLayer::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    bool MenuLayer::isFinished() const
    {
        return finished;
    }

    bool MenuLayer::onKeyPressed(Tempest::PressedKeyEvent& e)
    {
        return false;
    }

    bool MenuLayer::onKeyReleased(Tempest::ReleasedKeyEvent& e)
    {
        return false;
    }
}
