#include "Entity.h"

namespace game
{
    Entity::Entity() : 
        layer(0), _animationStartFrame(0), _animationEndFrame(0), _pausedFrame(0), _firstFrame(0),
        _animationPaused(false), _startedPlayingAnimation(false), _playingAnimation(false),
         _horizontalOrientation(false), _verticalOrientation(true)
    {
        _resourceManager = DEFAULT_RESOURCE_GROUP;
    }

    const std::shared_ptr<Animation> Entity::getActiveAnimation() const
    {
        return _activeAnimation;
    }

    const Tempest::ref<Tempest::SubTexture2D> Entity::getActiveAnimationFrame(int frameNumber)
    {
        //If there is an active animation
        if (_activeAnimation != nullptr && _activeAnimation->getTotalFrames() > 0) 
        {
            //Is the animation paused?
            if (_animationPaused) 
            {
                return _activeAnimation->getFrame(_pausedFrame);
            }

            //Started playing an animation if it was set to play before this frame
            if (_playingAnimation && _startedPlayingAnimation == false) 
            {
                _animationStartFrame = frameNumber;
                _animationEndFrame = frameNumber + _activeAnimation->getTotalFrames();
                _startedPlayingAnimation = true;
            }

            if (_playingAnimation) 
            {
                if (frameNumber >= _animationEndFrame) 
                {
                    //Stop playing the animation.
                    _activeAnimation = std::move(_queuedAnimation);
                    _playingAnimation = false;
                    _startedPlayingAnimation = false;

                    onPlayAnimationEnd();
                }
                else 
                {
                    //Return the frame from the currently playing animation.
                    return _activeAnimation->getFrameBySequence(frameNumber - (_animationEndFrame - _activeAnimation->getTotalFrames()));
                }
            }

            //Return the frame of the currently active animation.
            if (_activeAnimation != nullptr) 
            {
                return _activeAnimation->getFrame(frameNumber);
            }
        }
        //If we can switch to a non-null queued animation, do it
        else if (_queuedAnimation != nullptr) 
        {
            _activeAnimation = std::move(_queuedAnimation);
            _playingAnimation = false;
            _startedPlayingAnimation = false;
        }

        return nullptr;
    }

    const std::shared_ptr<Animation> Entity::getAnimation(const std::string& name) const
    {
        return _resourceManager->getAnimation(name);
    }

    double Entity::getAge() const 
    {
        return static_cast<double>(GAME_SESSION.world->getFrameCount() - _firstFrame) * GAME_SESSION.world->getDelta();
    }

    const std::shared_ptr<ResourceManager> Entity::getResourceManager() const 
    {
        return _resourceManager;
    }

    void Entity::setOrientation(Direction direction) 
    {
        switch (direction) 
        {
        case Direction::UP:
            _verticalOrientation = true;
            break;
        case Direction::DOWN:
            _verticalOrientation = false;
            break;
        case Direction::LEFT:
            _horizontalOrientation = false;
            break;
        case Direction::RIGHT:
            _horizontalOrientation = true;
            break;
        }
    }

    void Entity::pausedAnimation(bool paused, int pauseFrame)
    {
        _pausedFrame = paused;
        _pausedFrame = pauseFrame;
    }

    void Entity::playAnimation(const std::shared_ptr<Animation>& animation, const std::shared_ptr<Animation>& newAnimation) 
    {
        //Queue the current animation to play after this animation plays.
        if (newAnimation != nullptr)
        {
            _queuedAnimation = newAnimation;
        }
        else 
        {
            _queuedAnimation = _activeAnimation;
        }
        _playingAnimation = true;
        _activeAnimation = animation;
    }

    void Entity::playAnimation(const std::string& name)
    {
        playAnimation(getAnimation(name));
    }

    void Entity::playAnimation(const std::string& name, const std::string& nextAnimation)
    {
        playAnimation(getAnimation(name), getAnimation(nextAnimation));
    }

    void Entity::setAnimation(const std::shared_ptr<Animation>& animation)
    {
        //Queue the animation until the current one is done playing
        if (_playingAnimation)
        {
            _queuedAnimation = animation;
        }
        else 
        {
            _activeAnimation = animation;
        }

        //Also unpaused the animation if we are setting a new one.
        //setAnimationPaused(false);
    }

    void Entity::setAnimation(const std::string& name)
    {
        setAnimation(getAnimation(name));
    }
    
}