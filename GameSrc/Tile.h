#ifndef TILE_HDR
#define TILE_HDR

#include "Entity.h"

#include <Tempest.h>

namespace game 
{
    class Tile : public Entity 
    {
    public:
        virtual ~Tile() = default;

        double getWidth() const { _size.x; }
        double getHeight() const { _size.y; }
    };
}

#endif // !TILE_HDR
