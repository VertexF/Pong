#include "Animation.h"

namespace 
{
    int FRAME_INDEX = 0;
}

namespace game 
{
    Animation::Animation() : _duration(0), _frameIndex(0)
    {
    }

    void Animation::appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, int duration)
    {
        _frames.emplace_back(Tempest::SubTexture2D::createFromCoords(texture, coords, cellSize, spriteSize));
        _duration = duration;
    }

    void Animation::appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec4& coords, int duration)
    {
        _frames.emplace_back(Tempest::SubTexture2D::createFromCoords(texture, coords));
        _duration = duration;
    }

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrame(unsigned int frameNumber)
    {
        if (_duration > 1)
        {
            int index = static_cast<int>(frameNumber / _duration);
            if (_frames.size() == index)
            {
                index = 0;
            }
            return _frames.at(index);
        }
        else 
        {
            return _frames.at(0);
        }
    }

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrameBySequence(unsigned int sequence) const
    {
        return _frames[sequence];
    }
}