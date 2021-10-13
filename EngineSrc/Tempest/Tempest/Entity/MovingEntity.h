#ifndef MOVING_ENTITY_HDR
#define MOVING_ENTITY_HDR

#include "BaseGameEntity.h"

#include <glm/glm.hpp>

namespace Tempest 
{
    class MovingEntity : public BaseGameEntity
    {
    public:
        MovingEntity(const glm::vec3& position, double radius, const glm::vec3& velocity,
                     double maxSpeed, const glm::vec3& heading, double mass, 
                     const glm::vec3& scale, double turnRate, double maxForce);

        virtual ~MovingEntity() = default;

        glm::vec3 getVelocity() const;
        void setVelocity(const glm::vec3& vel);

        double getMass() const;

        glm::vec3 getSide() const;

        glm::vec3 getHeading() const;
        void setHeading(const glm::vec3& newHeading);
        bool rotateToFaceHeading(const glm::vec3& target);

        bool isSpeedMaxedOut() const;
        double getSpeed() const;
        double getSpeedSq() const;

        double getMaxSpeed() const;
        void setMaxSpeed(double max);

        double getMaxForce() const;
        void setMaxForce(double max);

        double getMaxTurnRate() const;
        void setMaxTurnRate(double max);

    private:
        glm::vec3 _velocity;

        //A normalised vector point in the direction the entity is heading.
        glm::vec3 _heading;

        //A vector perpendicular to the head vector.
        glm::vec3 _side;

        double _mass;

        //The maximum speed this entity may travel at.
        double _maxSpeed;

        //The maximum force of thrust forward.
        double _maxForce;

        //The maximum torque this vehicle can rotate.
        double _maxTurnRate;
    };
}

#endif // !MOVING_ENTITY_HDR