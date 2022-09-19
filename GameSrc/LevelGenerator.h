#ifndef LEVEL_GENERATOR_HDR
#define LEVEL_GENERATOR_HDR

#include <memory>
#include "Level.h"

namespace game 
{
    class LevelGenerator 
    {
    public:
        virtual ~LevelGenerator() = default;
    protected:
        virtual const std::shared_ptr<Level> generateLevel(int seed) const = 0;
    };
}

#endif // !LEVEL_GENERATOR_HDR
