#ifndef MOVING_ENTITY_HDR
#define MOVING_ENTITY_HDR

#include "BaseGameEntity.h"

#include <glm/glm.hpp>

namespace Tempest 
{
    class MovingEntity : public BaseGameEntity
    {
    public:
        MovingEntity(const glm::vec3& position, float radius, const glm::vec3& velocity,
                     float maxSpeed, const glm::vec3& heading, float mass, 
                     const glm::vec2& scale, float turnRate, float maxForce);

        virtual ~MovingEntity() = default;

        virtual void onUpdate(TimeStep time) = 0;
        virtual void onRender() = 0;

        virtual bool handleMessage(const Telegram& tele) = 0;

        virtual void write(std::ofstream outStream) = 0;
        virtual void read(std::ifstream inStream) = 0;

        glm::vec3 getVelocity() const;
        void setVelocity(const glm::vec3& vel);

        float getMass() const;

        glm::vec3 getSide() const;

        glm::vec3 getHeading() const;
        void setHeading(const glm::vec3& newHeading);
        bool rotateToFaceHeading(const glm::vec3& target);

        bool isSpeedMaxedOut() const;
        float getSpeed() const;
        float getSpeedSq() const;

        float getMaxSpeed() const;
        void setMaxSpeed(float max);

        float getMaxForce() const;
        void setMaxForce(float max);

        float getMaxTurnRate() const;
        void setMaxTurnRate(float max);

        glm::mat4 getTransform() const;

        void intergrate(Tempest::TimeStep ts);
        void calculateTransformMatrix();

    protected:
        glm::vec3 _velocity;

        //A normalised vector point in the direction the entity is heading.
        glm::vec3 _heading;

        //A vector perpendicular to the head vector.
        glm::vec3 _side;

        //This holds the translation from world to local and local to world basis.
        glm::mat4 _transformMatrix;

        float _mass;

        //The maximum speed this entity may travel at.
        float _maxSpeed;

        //The maximum force of thrust forward.
        float _maxForce;

        //The maximum torque this vehicle can rotate.
        float _maxTurnRate;

        //This stores the time used for intergration.
        float _time;
    };
}

#endif // !MOVING_ENTITY_HDR