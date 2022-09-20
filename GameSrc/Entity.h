#ifndef ENTITY_HDR
#define ENTITY_HDR

#include <memory>

#include <Tempest.h>

#include "Animation.h"

//double Entity::getBottom() const
//{
//    return getY();
//}
//
//double Entity::getCenterX() const
//{
//    return getX() + getWidth() / 2.0;
//}
//
//double Entity::getCenterY() const
//{
//    return getY() + getHeight() / 2.0;
//}
//
//double Entity::getLeft() const
//{
//    return getX();
//}
//
//const ResourceManager* Entity::getResourceManager() const
//{
//    return resourceManager;
//}
//
//double Entity::getRight() const
//{
//    return getX() + getWidth();
//}
//
//double Entity::getTop() const
//{
//    return getY() + getHeight();
//}

namespace game
{
    class Entity
    {
    public:
        Entity();
        virtual ~Entity() = default;

        const std::shared_ptr<Animation> getActiveAnimation() const;
        const Tempest::ref<Tempest::SubTexture2D> getActiveAnimationFrame() const;

        double getBottom() const { position.y; }
        double getLeft() const { position.x; }
        double getRight() const { position.x + _size.x; }
        double getTop() const { position.y + _size.y; }
        double getCenterX() const { getRight() / 2.0; }
        double getCenterY() const { getTop() / 2.0; }

        glm::f64vec2 position;
    protected:
        glm::f64vec2 _size;
    private:
        std::shared_ptr<Animation> _animation;
    };
}

#endif // !ENTITY_HDR
