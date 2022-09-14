#include "Background.h"

namespace game 
{
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

    Tempest::ref<Tempest::Texture2D> Background::getTexture() const
    {
        return _backgroundTexture;
    }
}