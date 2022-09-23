#include "Tile.h"

#include "ResourceManager.h"
#include "Animation.h"

namespace game 
{
    Tile::Tile(TileCollisionBehaviour type, bool tilesetEnabled) : _x(0), _y(0),
        _width(1), _height(1), _collisionBehaviour(type), _tilesetEnabled(tilesetEnabled)
    {
        setLayer(0);
    }

    Tile::TileCollisionBehaviour Tile::getCollisionBehaviour() const 
    {
        return _collisionBehaviour;
    }

    bool Tile::getEdgeState(Tile::Edge edge) const 
    {
        switch (_collisionBehaviour) 
        {
        case TileCollisionBehaviour::TILE_PLATFORM:
            return (edge == Edge::EDGE_TOP);
        case TileCollisionBehaviour::TILE_SLOPE_DOWN:
            return (edge == Edge::EDGE_BOTTOM);
        case TileCollisionBehaviour::TILE_SLOPE_UP:
            return (edge == Edge::EDGE_RIGHT);
        case TileCollisionBehaviour::TILE_SOLID:
            return true;
        default:
            break;
        }

        return false;
    }

    bool Tile::isSlope() const 
    {
        return (_collisionBehaviour == TileCollisionBehaviour::TILE_SLOPE_UP || _collisionBehaviour == TileCollisionBehaviour::TILE_SLOPE_DOWN);
    }

    void Tile::setHeight(int height) 
    {
        _height = height;
    }

    void Tile::setWidth(int width) 
    {
        _width = width;
    }

    void Tile::setLayer(int newlayer) 
    {
        this->layer = newlayer * 2;
    }

    const std::shared_ptr<Animation> Tile::getTilesetAnimation(int x, int y) 
    {
        std::shared_ptr<Animation> animation;
        //NOTE! I haven't added the rest of the rules for now.
        if (animation == nullptr) 
        {
            animation = getAnimation("tile");
        }

        return animation;
    }

}