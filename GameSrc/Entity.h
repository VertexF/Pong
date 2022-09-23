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

        I'm so leaving out bitmask for colour and offsets for rendering. I think our rendering API takes care of them for us.
    */
    class Entity
    {
    public:
        enum class Direction 
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
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

        void setOrientation(Direction direction);
        void pausedAnimation(bool paused, int pauseFrame = 0);

        //This function needs to implemented to render tiles in front or behind each other.
        virtual void setLayer(int layer) = 0;

        glm::f64vec2 position;
    protected:
        int layer;

        glm::f64vec2 size;

        virtual void onPlayAnimationEnd() = 0;
        virtual void onRender() = 0;

        void playAnimation(const std::shared_ptr<Animation>& animation, const std::shared_ptr<Animation>& newAnimation = nullptr);
        void playAnimation(const std::string& name);
        void playAnimation(const std::string& name, const std::string& nextAnimation);

        void setAnimation(const std::shared_ptr<Animation>& animation);
        void setAnimation(const std::string& name);

        const std::shared_ptr<Animation> getAnimation(const std::string& name) const;
    private:
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
