#ifndef BACKGROUND_HDR
#define BACKGROUND_HDR

#include <string>

#include <Tempest.h>
#include "Animation.h"

namespace game 
{
    class Background 
    {
    public:
        enum class BackgroundTiling
        {
            BACKGROUND_HORIZONTAL,
            BACKGROUND_VERTICAL,
            BACKGROUND_ALL
        };

    public:
        Background();
        ~Background() = default;
        Background(const std::string& path);

        void createTexture(const std::string& path);
        void addFrame(const Tempest::ref<Tempest::Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1, 1 }, int duration = 1);
        const BackgroundTiling getTiling() const;
        void setTiling(const BackgroundTiling& tiling);
        Tempest::ref<Tempest::Texture2D> getTexture() const;

        const std::shared_ptr<Animation> getAnimation() const;
    private:
        Tempest::ref<Tempest::Texture2D> _backgroundTexture;
        std::shared_ptr<Animation> _animation;
        BackgroundTiling _tiling;
    };
}

#endif // !BACKGROUND_HDR
