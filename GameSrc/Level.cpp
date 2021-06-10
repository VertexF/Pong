#include "PreComp.h"
#include "Level.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
    bool checkCollision(const glm::vec4& a, const glm::vec4& b)
    {
        //The sides of the rectangles
        float leftA, leftB;
        float rightA, rightB;
        float topA, topB;
        float bottomA, bottomB;

        //Calculate the sides of rect A
        leftA = a.x;
        rightA = a.x + a.z;
        topA = a.y;
        bottomA = a.y + a.w;

        //Calculate the sides of rect B
        leftB = b.x;
        rightB = b.x + b.z;
        topB = b.y;
        bottomB = b.y + b.w;

        //If any of the sides from A are outside of B
        if (bottomA <= topB)
        {
            return false;
        }

        if (topA >= bottomB)
        {
            return false;
        }

        if (rightA <= leftB)
        {
            return false;
        }

        if (leftA >= rightB)
        {
            return false;
        }

        //If none of the sides from A are outside B
        return true;
    }
}

void Level::init() 
{
    TEMPEST_PROFILE_FUNCTION();

    _level = L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
        L"WWWWWWWDDDDDDDDDDDWWWWWWWWWWWW"
        L"WWWWWWDDDDDDDDDDDDDDDWWWWWWWWW"
        L"WWWDDDDDDDDDDDDDDDDDDWWWWWWWWW"
        L"WWWDDDDDWWDDDDDDDDDDDWWWWWWWWW"
        L"WWWWDDDWWWWDDDDDDDDDDWWWWWWWWW"
        L"WWWWDDDWWWWDDDDDDDDDWWWWWWWWWW"
        L"WWDDDDDDDDDDDDDDDDDDDWWWWWWWWW"
        L"WWWWDDDDDDDDDDDDDDDWWWWWWWWWWW"
        L"WWWWDDDDDDDDDDDDDDDDWWWWWWWWWW"
        L"WWWDDDDDDDDDDDDDDDDDWWWWWWWWWW"
        L"WWWWDDDDDDDDDDDDDDDDDDDDDDDWWW"
        L"WWWWWWWWDDDDDDDDDDDDDDDDDDDDWW"
        L"WWWWWDDDDDDDDDDDDDDDDDDDDDDDWW"
        L"WWWWWDDDDDDDDDDDDDDDDDDDDDDWWW"
        L"WWWWDDDDDDDDDDDDDDDDDDDDDDDWWW"
        L"WWWWWWDDDDDDDDDDDDDDDDDDDDDWWW"
        L"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW";

    _spriteSheetLevel = Tempest::Texture2D::create("Assets/Textures/RPGpack_sheet_2X.png");

    _bushTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 1, 11 }, { 128, 128 });
    _treeTexture = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 2, 1 }, { 128, 128 }, { 1, 2 });
    _textureMap['D'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 6, 11 }, { 128, 128 });
    _textureMap['W'] = Tempest::SubTexture2D::createFromCoords(_spriteSheetLevel, { 11, 11 }, { 128, 128 });

    _mapHeight = _level.length() / _mapWidth;
}

void Level::onUpdate(Tempest::TimeStep ts) 
{
    TEMPEST_PROFILE_FUNCTION();

    for (uint32_t y = 0; y < _mapHeight; ++y)
    {
        for (uint32_t x = 0; x < _mapWidth; ++x)
        {
            if (touchesWall(_player.getQuad(), x, y))
            {
                _player.collisionChange();
            }
        }
    }

    _player.onUpdate(ts);
}

void Level::onRender() 
{
    TEMPEST_PROFILE_FUNCTION();

    for (uint32_t y = 0; y < _mapHeight; ++y)
    {
        for (uint32_t x = 0; x < _mapWidth; ++x)
        {
            wchar_t tileType = getTile(x, y);
            if (_textureMap.find(tileType) != _textureMap.end())
            {
                Tempest::Renderer2D::drawQuad({ x - _mapWidth / 2.f, y - _mapHeight / 2.f, 0.5f }, { 1.f, 1.f }, _textureMap[tileType]);
            }
            else
            {
                Tempest::Renderer2D::drawQuad({ x - _mapWidth / 2.f, y - _mapHeight / 2.f, -1.0f }, { 1.f, 1.f }, { 1.0, 0.0, 1.0, 1.0 });
            }
        }
    }

    Tempest::Renderer2D::drawQuad({ 0.f, 0.f, 0.0f }, { 1.f, 1.f }, _bushTexture);
    Tempest::Renderer2D::drawQuad({ 1.f, 0.5f, 0.0f }, { 1.f, 2.f }, _treeTexture);

    _player.onRender();
}

void Level::onImGuiRender() 
{
    TEMPEST_PROFILE_FUNCTION();
    _player.onImGuiRender();
}

void Level::reset()
{
    TEMPEST_PROFILE_FUNCTION();
    _gameOver = false;

    _player.reset();
}

bool Level::touchesWall(const glm::vec4& box, uint32_t x, uint32_t y)
{
    ////If the tile is a wall type tile
    //if (getTile(x, y) == L'D')
    //{
    //    //If the collision box touches the wall tile
    //    if (checkCollision(box, {x, y, 1.f, 1.f}) == false)
    //    {
    //        return true;
    //    }
    //}

    //If no wall tiles were touched
    return false;
}