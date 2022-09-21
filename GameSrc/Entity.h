#ifndef ENTITY_HDR
#define ENTITY_HDR

#include <memory>
#include <string>

#include <Tempest.h>

#include "Animation.h"
#include "Global.h"
#include "ResourceManager.h"

namespace game
{
    /*
        Removing Entity getWorld() stuff because it's copying a unique_ptr in my code but more importantly there is 1 world per game 
        application so GAME_SESSION.world->getStuff() is the way I'm choosing to get world state. Please review later.
    */
    class Entity
    {
    public:
        Entity();
        virtual ~Entity() = default;

        const std::shared_ptr<Animation> getActiveAnimation() const;
        const Tempest::ref<Tempest::SubTexture2D> getActiveAnimationFrame(int framenumber);

        double getAge() const;
        const std::shared_ptr<ResourceManager> getResourceManager() const;

        double getBottom() const { return position.y; }
        double getLeft() const { return position.x; }
        double getRight() const { return position.x + size.x; }
        double getTop() const { return position.y + size.y; }
        double getCenterX() const { return getRight() / 2.0; }
        double getCenterY() const { return getTop() / 2.0; }

        glm::f64vec2 position;
    protected:
        int layer;

        glm::f64vec2 size;
    private:
        const std::shared_ptr<Animation> getAnimation(const std::string& name) const;

        std::shared_ptr<Animation> _activeAnimation;
        std::shared_ptr<Animation> _queuedAnimation;
        std::shared_ptr<ResourceManager> _resourceManager;

        int _animationStartFrame;
        int _animationEndFrame;
        int _pausedFrame;
        int _firstFrame;

        bool _startedPlayingAnimation;
        bool _animationPaused;
        bool _playingAnimation;
        bool _horizontalOrientation;
        bool _verticalOrientation;
    };
}

#endif // !ENTITY_HDR
