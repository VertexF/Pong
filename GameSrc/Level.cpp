#include "Level.h"

namespace game 
{
    Level::Level(int width, int height) :
        _width(width), _height(height)
    {
    }

    void Level::setTheme(const std::shared_ptr<LevelTheme>& theme)
    {
        setBackground(theme->getBackground(0));
    }

    void Level::setBackground(const std::shared_ptr<Background>& background)
    {
        _background = background;
    }

    std::shared_ptr<Background> Level::getBackground() const
    {
        return _background;
    }
}