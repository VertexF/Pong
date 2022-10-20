#ifndef ENTITY_HDR
#define ENTITY_HDR

#include <memory>
#include <string>

#include <Tempest.h>

namespace game
{
    class Entity
    {
    public:
        enum class Direction 
        {
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
    public:
        Entity();
        virtual ~Entity() = default;

        double getAge() const;

        double getBottom() const { return position.y; }
        double getLeft() const { return position.x; }
        double getRight() const { return position.x + size.x; }
        double getTop() const { return position.y + size.y; }
        double getCenterX() const { return getRight() / 2.0; }
        double getCenterY() const { return getTop() / 2.0; }

        void setOrientation(Direction direction);

        //This function needs to implemented to render tiles in front or behind each other.
        virtual void setLayer(int layer) = 0;

        glm::vec3 position;
    protected:
        int layer;

        glm::vec3 size;

        virtual void onPlayAnimationEnd() = 0;
        virtual void onRender() = 0;
    };
}

#endif // !ENTITY_HDR
