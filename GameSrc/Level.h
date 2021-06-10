#ifndef LEVEL_HDR
#define LEVEL_HDR

#include "Player.h"
#include "Tempest/Renderer/Texture.h"
#include "Tempest/Renderer/SubTexture2D.h"

class Level 
{
public:
    void init();
    void onUpdate(Tempest::TimeStep ts);
    void onRender();

    void onImGuiRender();

    bool isGameOver() const { return _gameOver; }
    void reset();

    const Player& getPlayer() const { return _player; }

    // Utility Lambdas
    wchar_t getTile(uint32_t x, uint32_t y) const
    {
        if (x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight)
        {
            return _level[y * _mapWidth + x];
        }
        else
        {
            return L' ';
        }
    };

    void setTile(uint32_t x, uint32_t y, wchar_t c)
    {
        if (x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight)
        {
            _level[y * _mapWidth + x] = c;
        }
    };
private:
    bool touchesWall(const glm::vec4& box, uint32_t x, uint32_t y);
private:
    Player _player;

    Tempest::ref<Tempest::Texture2D> _backgroundTexture;
    Tempest::ref<Tempest::Texture2D> _spriteSheetLevel;
    Tempest::ref<Tempest::SubTexture2D> _bushTexture;
    Tempest::ref<Tempest::SubTexture2D> _treeTexture;

    const uint32_t _mapWidth = 30;
    uint32_t _mapHeight;

    std::unordered_map<wchar_t, Tempest::ref<Tempest::SubTexture2D>> _textureMap;

    bool _gameOver = false;

    std::wstring _level;
};

#endif // !LEVEL_HDR
