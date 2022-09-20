#include "Entity.h"

namespace game
{
    Entity::Entity()
    {
        _defaultResourceManager = DEFAULT_RESOURCE_GROUP;
    }

    const std::shared_ptr<Animation> Entity::getActiveAnimation() const
    {
        return _animation;
    }

    const Tempest::ref<Tempest::SubTexture2D> Entity::getActiveAnimationFrame() const
    {
        return nullptr;
    }

    std::shared_ptr<Animation> Entity::getAnimation(const std::string& name) const
    {
        return _defaultResourceManager->getAnimation(name);
    }
}