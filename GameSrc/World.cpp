#include "World.h"

#include "Episode.h"

namespace game 
{
    World::World() :_frameCount(0), _levelWidth(0), _levelHeight(0)
    {
    }

    void World::setLevel(const std::shared_ptr<Level>& newLevel)
    {
        unloadLevel();
        loadLevel(newLevel);
    }

    void World::render()
    {
        // Render the background
        if (_background != nullptr)
        {
            Tempest::ref<Tempest::SubTexture2D> animation = _background->getAnimation()->getFrame(_frameCount);

            glm::vec2 cellSize = { 16, 9 };

            //This is flawed as we might not be able to tile backgrounds if the level width and height is weird.
            switch (_background->getTiling()) 
            {
            case Background::BackgroundTiling::BACKGROUND_HORIZONTAL:
                for (int x = 0; x < _levelWidth; x += cellSize.x) 
                {
                    Tempest::Renderer2D::drawQuad({ x, 0 }, cellSize, animation);
                }
                break;
            case Background::BackgroundTiling::BACKGROUND_VERTICAL:
                for (int y = 0; y < _levelHeight; y += cellSize.y)
                {
                    Tempest::Renderer2D::drawQuad({ 0, -y }, cellSize, animation);
                }
                break;
            case Background::BackgroundTiling::BACKGROUND_ALL:
                for (int x = 0; x < _levelWidth; x += cellSize.x)
                {
                    for (int y = 0; y < _levelHeight; y += cellSize.y)
                    {
                        Tempest::Renderer2D::drawQuad({ x, -y }, cellSize, animation);
                    }
                }
                break;
            }

            //Is this what we want for backgrounds?
            //Consider the fact we might need to keep track of different things for different backgrounds.
            if (_frameCount >= _background->getAnimation()->getTotalFrames())
            {
                _frameCount = 0;
            }
            _frameCount++;
        }
    }

    void World::unloadLevel()
    {
        _background.reset();
    }

    void World::loadLevel(const std::shared_ptr<Level>& newLevel)
    {
        // Set the background
        _background = newLevel->getBackground();
        _levelWidth = newLevel->getWidth();
        _levelHeight = newLevel->getHeight();

        _frameCount = 0;
    }
}