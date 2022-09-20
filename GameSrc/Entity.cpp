#include "Entity.h"

namespace game 
{
    Entity::Entity() 
    {
    }

    const std::shared_ptr<Animation> Entity::getActiveAnimation() const 
    {
        return _animation;
    }

    const Tempest::ref<Tempest::SubTexture2D> Entity::getActiveAnimationFrame() const 
    {
        return nullptr;
    }
}