#ifndef TILE_HDR
#define TILE_HDR

#include "Entity.h"

namespace game 
{
    class Tile : public Entity 
    {
    public:
        virtual ~Tile() = default;
    };
}

#endif // !TILE_HDR
