#ifndef BACKGROUND_HDR
#define BACKGROUND_HDR

#include <string>

#include <Tempest.h>

namespace game 
{
    class Background 
    {
    public:
        Background() = default;
        ~Background() = default;
        Background(const std::string& path);

        void createTexture(const std::string& path);
        Tempest::ref<Tempest::Texture2D> getTexture() const;

        enum class BackgroundTiling
        {
            BACKGROUND_HORIZONTAL,
            BACKGROUND_VERTICAL,
            BACKGROUND_ALL,
        };
    private:
        Tempest::ref<Tempest::Texture2D> _backgroundTexture;
    };
}

#endif // !BACKGROUND_HDR
