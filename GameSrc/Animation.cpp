#include "Animation.h"

namespace game 
{
    Animation::Animation() 
    {
    }

    void Animation::appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize, int duration)
    {
        for (int i = 0; i < duration; i++)
        {
            _frames.emplace_back(Tempest::SubTexture2D::createFromCoords(texture, coords, cellSize, spriteSize));
        }
    }

    void Animation::appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec4& coords, int duration)
    {
        for (int i = 0; i < duration; i++)
        {
            _frames.emplace_back(Tempest::SubTexture2D::createFromCoords(texture, coords));
        }
    }

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrame(unsigned int frameNumber) const
    {
        unsigned int index = frameNumber % _frames.size();
        return _frames[index];
    }

    const Tempest::ref<Tempest::SubTexture2D> Animation::getFrameBySequence(unsigned int sequence) const
    {
        return _frames[sequence];
    }
}