#ifndef TEST_LEVEL_GENERATOR_HDR
#define TEST_LEVEL_GENERATOR_HDR

#include "LevelGenerator.h"

namespace game 
{
    class TestLevelGenerator : public LevelGenerator
    {
    public:
        virtual ~TestLevelGenerator() = default;
        virtual const std::shared_ptr<Level> generateLevel(int seed) const override;
    };
}

#endif // !TEST_LEVEL_GENERATOR_HDR
