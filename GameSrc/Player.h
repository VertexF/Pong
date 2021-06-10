#ifndef PLAYER_HDR
#define PLAYER_HDR

#include <Tempest.h>

#include "Player.h"

class Player 
{
public:
    Player();

    void loadAssets();
    void onUpdate(Tempest::TimeStep ts);
    void onRender();

    void onImGuiRender();
    void reset();

    void collisionChange() { _playerDebugColour = { 0.f, 1.f, 1.f, 1.f }; }

    float getRotation() { return _rotation; }
    const glm::vec2& getPosition() const { return { _playerQuad.x, _playerQuad.y }; }
    const glm::vec4& getQuad() const { return _playerQuad; }
private:
    glm::vec2 _velocity = { 0.f, 0.f };

    glm::vec4 _playerDebugColour = { 1.f, 0.f, 1.f, 1.f };
    glm::vec4 _playerQuad = { 0.f, 0.f, 1.f, 1.f };

    Tempest::ref<Tempest::Texture2D> _leonTexture;

    float _playerMovementSpeed = 5.0f;

    float _rotation = 0.f;
};

#endif // !PLAYER_HDR
