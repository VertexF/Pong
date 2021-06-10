#include "PreComp.h"
#include "Player.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Tempest/Core/Input.h"

Player::Player()
{
    _leonTexture = Tempest::Texture2D::create("Assets/Textures/Me.png");
}

void Player::loadAssets() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::onUpdate(Tempest::TimeStep ts)
{
    TEMPEST_PROFILE_FUNCTION();

    if (Tempest::Input::isKeyPressed(TEMP_KEY_W))
    {
        _playerQuad.y += _playerMovementSpeed * ts;
    }
    else if (Tempest::Input::isKeyPressed(TEMP_KEY_S))
    {
        _playerQuad.y -= _playerMovementSpeed * ts;
    }

    if (Tempest::Input::isKeyPressed(TEMP_KEY_A))
    {
        _playerQuad.x -= _playerMovementSpeed * ts;
    }
    else if (Tempest::Input::isKeyPressed(TEMP_KEY_D))
    {
        _playerQuad.x += _playerMovementSpeed * ts;
    }
}

void Player::onRender() 
{
    TEMPEST_PROFILE_FUNCTION();

    Tempest::Renderer2D::drawQuad({ _playerQuad.x, _playerQuad.y, -0.2f }, { _playerQuad.z, _playerQuad.w }, {0.0, 0.0, 0.0, 1.0});
}

void Player::onImGuiRender() 
{
    TEMPEST_PROFILE_FUNCTION();
}

void Player::reset() 
{
    _playerQuad.x = 0.f;
    _playerQuad.y = 0.f;
    _velocity = { 0.0f, 0.0f };
}