#ifndef BASE_ENTITY_HDR
#define BASE_ENTITY_HDR

#include <memory>
#include <string>

#include <Tempest.h>

namespace game
{
    class BaseEntity
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
        BaseEntity();
        virtual ~BaseEntity() = default;

        double getAge() const;

        double getBottom() const { return position.y; }
        double getLeft() const { return position.x; }
        double getRight() const { return position.x + size.x; }
        double getTop() const { return position.y + size.y; }
        double getCenterX() const { return getRight() / 2.0; }
        double getCenterY() const { return getTop() / 2.0; }

        void setOrientation(Direction direction);

        virtual void onUpdate(Tempest::TimeStep timeStep) = 0;

        //This function needs to implemented to render tiles in front or behind each other.
        virtual void setLayer(float layer) = 0;

        virtual glm::vec3 getAcceleration() const = 0;
        virtual void setAcceleration(const glm::vec3 accel) = 0;

        virtual glm::vec3 getVelocity() const = 0;
        virtual void setVelocity(const glm::vec3 vel) = 0;

        virtual glm::vec3 getPosition() const = 0;
        virtual void getPosition(const glm::vec3 pos) = 0;

        virtual double getMaxSpeed() const = 0;
        virtual void setMaxSpeed(double speed) = 0;

        virtual double getMaxSteeringForce() const = 0;
        virtual void setMaxSteeringForce(double force) = 0;

        glm::vec3 position;
    protected:
        float layer;

        glm::vec2 size;
        glm::vec3 acceleration;
        glm::vec3 velocity;

        virtual void onRender() = 0;
    };
}

#endif // !BASE_ENTITY_HDR
