#include "PreComp.h"
#include "Game2D.h"

#include "Global.h"
#include "World.h"
#include "Episode.h"

#include "LevelGenerator.h"
#include "TestLevelGenerator.h"

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
    }

    void Game2D::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        std::unique_ptr<TestLevelGenerator> generators = std::make_unique<TestLevelGenerator>();
        const std::vector<std::shared_ptr<LevelTheme>> themes = RESOURCE_MANAGER.getLevelThemes();

        std::shared_ptr<Level> currentLevel = generators->generateLevel(0);
        currentLevel->setTheme(themes.at(0));
        GAME_SESSION.episode->addGameLevel(1, currentLevel);
        GAME_SESSION.world->setLevel(currentLevel);

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

        if (Tempest::Input::isKeyPressed(TEMP_KEY_SPACE)) 
        {
            std::unique_ptr<TestLevelGenerator> generators = std::make_unique<TestLevelGenerator>();

            std::shared_ptr<Level> currentLevel = generators->generateLevel(0);
            currentLevel->setTheme(RESOURCE_MANAGER.getLevelTheme("smb3_dead_grass_theme"));
            GAME_SESSION.episode->addGameLevel(2, currentLevel);
            GAME_SESSION.world->setLevel(currentLevel);
        }

        _cameraController->setCameraPosition({ _posX, _posY, 0.0f });

        Tempest::Renderer2D::resetStats();

        Tempest::Renderer2D::beginScene(_cameraController->getCamera());

        GAME_SESSION.world->render();

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
