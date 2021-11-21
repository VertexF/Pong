#ifndef RIGID_BODY_HDR
#define RIGID_BODY_HDR

#include <glm/glm.hpp>
#include "../Core/TimeStep.h"

namespace Tempest 
{
    class RigidBody
    {
    public:
        RigidBody(const glm::vec3& position, const glm::vec3& velocity,
                     float maxSpeed, const glm::vec3& heading, float mass, 
                     const glm::vec2& scale, float turnRate, float maxForce);

        virtual ~RigidBody() = default;

        glm::vec3 getPosition() const;
        void setPosition(const glm::vec3& pos);

        glm::vec3 getVelocity() const;
        void setVelocity(const glm::vec3& vel);

        glm::vec3 getAcceleration() const;
        void setAcceleration(const glm::vec3& acc);

        glm::vec2 getScale() const;
        void setScale(const glm::vec2& value);
        void setScale(float value);

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
        void clearAccumlator();
        void calculateTransformMatrix();

    protected:
        glm::vec3 _acceleration;
        glm::vec3 _velocity;
        glm::vec3 _position;
        glm::vec2 _scale;

        glm::vec3 _forceAccumate;
        glm::vec3 _torqueAccumate;

        glm::vec3 _lastFrameAcceleration;

        glm::vec3 _rotation;

        glm::vec3 _angularAcceleration;

        float linearDamping;
        float angularDamping;

        glm::quat _orientation;

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
    };
}

#endif // !MOVING_ENTITY_HDR