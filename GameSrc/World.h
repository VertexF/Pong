#ifndef WORLD_HDR
#define WORLD_HDR

#include <memory>

#include <Tempest.h>

#include "Level.h"
#include "Background.h"

namespace game
{
    class World 
    {
    public:
        World();
        void setLevel(const std::shared_ptr<Level>& newLevel);

        void render();
    private:
        void unloadLevel();
        void loadLevel(const std::shared_ptr<Level>& newLevel);

        std::shared_ptr<Background> _background;
        int _frameCount;

        int _levelWidth;
        int _levelHeight;
    };
}

#endif // !WORLD_HDR
