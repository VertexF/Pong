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

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrame(uint32_t frameNumber)
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

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrameBySequence(uint32_t sequence) const
    {
        //TODO: When your brain isn't fucked check this is same as the one in mario port.
        int index = static_cast<int>(sequence / _duration);
        return _frames[index];
    }
}