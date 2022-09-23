#ifndef TILE_HDR
#define TILE_HDR

#include <memory>

#include <Tempest.h>

#include "Entity.h"

namespace game 
{
    //WARNING NOT IMPLEMENTED!
    //I just need this evere for future implementation.
    class Sprite;

    //Every entity in that doesn't move.
    class Tile : public Entity 
    {
    public:
        //Tile collision behaviour
        enum class TileCollisionBehaviour 
        {
            TILE_NONE, //No collision
            TILE_PLATFORM, //One-way just the top side is collidable.
            TILE_SLOPE_DOWN, //Downward slope.
            TILE_SLOPE_UP, //Upward slope
            TILE_SOLID //All around solid block.
        };

        enum class Edge
        {
            EDGE_BOTTOM,
            EDGE_LEFT,
            EDGE_RIGHT,
            EDGE_TOP
        };
    public:
        //The tilesetEnable is about if the tile should be rendered based on the surrounding tiles.
        Tile(TileCollisionBehaviour type, bool tilesetEnabled = false);
        virtual ~Tile() = default;

        TileCollisionBehaviour getCollisionBehaviour() const;

        bool getEdgeState(Edge edge) const;

        int getIntWidth() const { return static_cast<int>(size.x); }
        double getWidth() const { return size.x; }
        int getIntHeight() const { return static_cast<int>(size.y); }
        double getHeight() const { return size.y; }

        int getIntX() const { return static_cast<int>(position.x); }
        int getIntY() const { return static_cast<int>(position.y); }

        bool isSlope() const;

        void setHeight(int height);
        void setWidth(int width);
        virtual void setLayer(int newlayer) override;

        const std::shared_ptr<Animation> getTilesetAnimation(int x, int y);
    private:
        virtual void onCollision(Sprite& sprite, Edge edge) {}
        virtual void onInit() {}

        virtual void onPlayAnimationEnd() {}
        virtual void onRender() {}
    private:
        int _x;
        int _y;
        int _width;
        int _height;
        TileCollisionBehaviour _collisionBehaviour;
        bool _tilesetEnabled;
    };
}

#endif // !TILE_HDR
