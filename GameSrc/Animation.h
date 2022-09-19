#ifndef ANIMATION_HDR
#define ANIMATION_HDR

#include <vector>

#include <Tempest.h>

namespace game 
{
    class Animation 
    {
    public:
        Animation();

        void appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 }, int duration = 1);
        void appendFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec4& coords, int duration = 1);

        const Tempest::ref<Tempest::SubTexture2D> getFrame(unsigned int frameNumber);
        const Tempest::ref<Tempest::SubTexture2D> getFrameBySequence(unsigned int sequence) const;

        size_t getTotalFrames() const { return _frames.size() * _duration; }
    private:
        std::vector<Tempest::ref<Tempest::SubTexture2D>> _frames;
        int _duration;
        int _frameIndex;
    };
}

#endif // !ANIMATION_HDR
