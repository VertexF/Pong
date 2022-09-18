#include "Background.h"

namespace game 
{
    Background::Background() : _tiling(BackgroundTiling::BACKGROUND_HORIZONTAL)
    {
        _animation = std::make_shared<Animation>();
    }

    Background::Background(const std::string& path)
    {
        //TODO: check if moving is possible. I think it will be but for now we are keeping it simple for my own sanity.
        _backgroundTexture = Tempest::Texture2D::create(path);
    }

    void Background::createTexture(const std::string& path)
    {
        if (_backgroundTexture.get() == nullptr) 
        {
            //TODO: check if moving is possible. I think it will be but for now we are keeping it simple for my own sanity.
            _backgroundTexture = Tempest::Texture2D::create(path);
        }
    }

    void Background::addFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, int duration)
    {
        _animation->appendFrame(texture, coords, cellSize, spriteSize, duration);
    }

    Tempest::ref<Tempest::Texture2D> Background::getTexture() const
    {
        return _backgroundTexture;
    }

    const Background::BackgroundTiling Background::getTiling() const
    {
        return _tiling;
    }

    void Background::setTiling(const Background::BackgroundTiling& tiling)
    {
        _tiling = tiling;
    }

    const std::shared_ptr<Animation> Background::getAnimation() const
    {
        return _animation;
    }
}