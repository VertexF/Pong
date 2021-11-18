#include "MovingEntity.h"

#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: Since I can actually write code that works in 3D space. I think I should re-write this like the Rigid body class in the old engine.
//With the GLM as the underlying maths so I can get that sweet SSE.
//Reason being, I'm literally already rewriting the RigidBody class anyway, the intergration set is LITERALLY exactly the same code. Apart 
//from the fact the force is generated outside of the class as AI stuff. There is nothing new here what I did worked and it's basically
//already 3D anyway so why shouldn't we?

//List of stuff to:
//1) Rip out the the BaseEntity

namespace Tempest 
{
    MovingEntity::MovingEntity(const glm::vec3& position, float radius, const glm::vec3& velocity,
                              float maxSpeed, const glm::vec3& heading, float mass,
                              const glm::vec2& scale, float turnRate, float maxForce) 
                              : BaseGameEntity(0, position, radius),
                               _velocity(velocity),
                               _heading(heading),
                               _mass(mass),
                               _side(glm::perp(heading, glm::vec3(1.0, 0.0, 1.0))),
                               _maxSpeed(maxSpeed),
                               _maxTurnRate(turnRate),
                               _maxForce(maxForce),
                               _transformMatrix(1.f),
                               _rotationMatrix(1.f),
                               _time(0.f)
    {
        _scale = scale;
    }

    glm::vec3 MovingEntity::getVelocity() const 
    {
        return _velocity;
    }

    void MovingEntity::setVelocity(const glm::vec3& vel) 
    {
        _velocity = vel;
    }

    float MovingEntity::getMass() const 
    {
        return _mass;
    }

    glm::vec3 MovingEntity::getSide() const 
    {
        return _side;
    }

    glm::vec3 MovingEntity::getHeading() const 
    {
        return _heading;
    }

    void MovingEntity::setHeading(const glm::vec3& newHeading) 
    {
        if (glm::epsilonEqual(glm::length2(newHeading), 00000001.f, 00000000001.f) == false)
        {
            _heading = newHeading;
            _side = glm::perp(_heading, glm::vec3(1.0, 0.0, 1.0));
        }
    }

    //! @ brief Given a target psoition, this method rotates the entity's heading
    //! and side vectors by an amount not greater than _maxTurnRate until directly
    //! faces the target.
    //! @return true when the heading is facing in the desired direction.
    bool MovingEntity::rotateToFaceHeading(const glm::vec3& target) 
    {
        glm::vec3 delta = target - _pos;

        if (glm::epsilonEqual(glm::length(delta), 0.f, 0.0000000001f) == false)
        {
            glm::vec3 toTarget = glm::normalize(delta);

            //First determine the angle between the heading vector and the target.
            float dotProduct = glm::dot(_heading, toTarget);
            float angle = glm::acos(dotProduct);

            //Return true if the entity is facing the target.
            if (dotProduct < 0.0000001f)
            {
                return true;
            }

            _rotationMatrix = glm::rotate(glm::mat4x4(1.f), glm::radians(angle * glm::sign(dotProduct)), { 0.f, 0.f, 1.f });

            _heading = glm::vec4(_heading, 1.f) * _transformMatrix;
            _velocity = glm::vec4(_velocity, 1.f) * _transformMatrix;

            _side = glm::perp(_heading, glm::vec3(0.f, 1.f, 1.f));

            return false;
        }

        return true;
    }

    bool MovingEntity::isSpeedMaxedOut() const 
    {
        return (_maxSpeed * _maxSpeed) >= (getSpeedSq());
    }

    float MovingEntity::getSpeed() const 
    {
        return glm::length(_velocity);
    }

    float MovingEntity::getSpeedSq() const 
    {
        return glm::length2(_velocity);
    }

    float MovingEntity::getMaxSpeed() const 
    {
        return _maxSpeed;
    }

    void MovingEntity::setMaxSpeed(float max) 
    {
        _maxSpeed = max;
    }

    float MovingEntity::getMaxForce() const 
    {
        return _maxForce;
    }

    void MovingEntity::setMaxForce(float max) 
    {
        _maxForce = max;
    }

    float MovingEntity::getMaxTurnRate() const 
    {
        return _maxTurnRate;
    }

    void MovingEntity::setMaxTurnRate(float max) 
    {
        _maxTurnRate = max;
    }

    glm::mat4 MovingEntity::getTransform() const 
    {
        return _transformMatrix;
    }

    void MovingEntity::wrapAround(glm::vec3& position, float screenWidth, float screenHeight) 
    {
        //TODO: Get better at the maths that requires that you understand how you do this without hacks.

        if (position.x > screenWidth + 9.6f) 
        {
            position.x = -9.5f;
        }

        if (position.x < -9.6f)
        {
            position.x = screenWidth + 9.5f;
        }

        if (position.y < -5.6f)
        {
            position.y = screenHeight + 5.f;
        }

        if (position.y > screenHeight + 4.5f)
        {
            position.y = -5.0f;
        }

    }

    void MovingEntity::intergrate(Tempest::TimeStep ts)
    {
        //_time += ts;

        glm::vec3 oldPos = getPos();
        glm::vec3 steeringForce = { 0.f, 0.f, 0.f }; //= _steeringBehavior->calculate();

        glm::vec3 acceleration = steeringForce / _mass;

        _velocity += acceleration * static_cast<float>(ts);

        //Calculating drag force.
        if (glm::length(_velocity) > _maxSpeed) 
        {
            _velocity = glm::normalize(_velocity);
            _velocity *= _maxSpeed;
        }

        _pos += _velocity * static_cast<float>(ts);

        if (glm::epsilonEqual(glm::length2(_velocity), 0.f, 00000000001.f) == false)
        {
            _heading = glm::normalize(_velocity);
            _side = glm::perp(_heading, glm::vec3(1.0, 0.0, 1.0));
        }

        //wrapAround(_pos, 1.f, 1.f);

        calculateTransformMatrix();
    }

    void MovingEntity::calculateTransformMatrix()
    {
        _transformMatrix = glm::translate(glm::mat4x4(1.f), _pos) * _rotationMatrix;

        _transformMatrix = glm::inverse(_transformMatrix);
    }
}