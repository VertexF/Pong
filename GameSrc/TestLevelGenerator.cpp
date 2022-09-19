#include "TestLevelGenerator.h"

namespace game 
{
    const std::shared_ptr<Level> TestLevelGenerator::generateLevel(int seed) const 
    {
        std::shared_ptr<Level> level = std::make_shared<Level>(256, 32);

        return level;
    }
}