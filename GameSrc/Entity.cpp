#include "Entity.h"

//layer(0),
//activeAnimation(nullptr),
//queuedAnimation(nullptr),
//playingAnimation(false),
//startedPlayingAnimation(false),
//horizontalOrientation(false),
//verticalOrientation(true),
//animationPaused(false),
//alpha(1.0f),
//redMask(1.0f),
//greenMask(1.0f),
//blueMask(1.0f),
//world(nullptr)

namespace game
{
    Entity::Entity() : 
        layer(0), _animationStartFrame(0), _animationEndFrame(0), _pausedFrame(0), _firstFrame(0),
        _animationPaused(false), _startedPlayingAnimation(false), _playingAnimation(false),
         _horizontalOrientation(false), _verticalOrientation(true)
    {
        _defaultResourceManager = DEFAULT_RESOURCE_GROUP;
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

                    //onAnimationEnd();
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
        return _defaultResourceManager->getAnimation(name);
    }

    double Entity::getAge() const 
    {
        if (_world == nullptr) 
        {
            return 0.0;
        }
        return static_cast<double>(_world->getFrameCount() - _firstFrame) * _world->getDelta();
    }
}