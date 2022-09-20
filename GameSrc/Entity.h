#ifndef ENTITY_HDR
#define ENTITY_HDR

#include <memory>
#include <string>

#include <Tempest.h>

#include "Animation.h"
#include "global.h"

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

        std::shared_ptr<Animation> getAnimation(const std::string& name) const;

        std::shared_ptr<Animation> _animation;
        std::shared_ptr<ResourceManager> _defaultResourceManager;
    };
}

#endif // !ENTITY_HDR
