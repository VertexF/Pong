#include "MovingEntity.h"

#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/transform.hpp>

namespace Tempest 
{
    MovingEntity::MovingEntity(const glm::vec3& position, double radius, const glm::vec3& velocity,
                              double maxSpeed, const glm::vec3& heading, double mass,
                              const glm::vec3& scale, double turnRate, double maxForce) 
                              : BaseGameEntity(0, position, radius),
                               _velocity(velocity),
                               _heading(heading),
                               _mass(mass),
                               _side(glm::perp(heading, glm::vec3(1.0, 0.0, 1.0))),
                               _maxSpeed(maxSpeed),
                               _maxTurnRate(turnRate),
                               _maxForce(maxForce)
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

    double MovingEntity::getMass() const 
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
        glm::vec3 toTarget = glm::normalize(target - _pos);

        //First determine the angle between the heading vector and the target.
        float dotProduct = glm::dot(_heading, toTarget);
        float angle = glm::acos(dotProduct);

        //Return true if the entity is facing the target.
        if (angle < 0.0000001) 
        {
            return true;
        }

        glm::mat4x4 rotationMatrix = glm::rotate(glm::mat4x4(1.f), glm::radians(angle * glm::sign(dotProduct)), { 0.f, 0.f, 1.f });

        _heading = rotationMatrix * glm::vec4(_heading, 1.f);
        _velocity = rotationMatrix * glm::vec4(_velocity, 1.f);
        
        _side = glm::perp(_heading, glm::vec3(1.0, 0.0, 1.0));

        return false;
    }

    bool MovingEntity::isSpeedMaxedOut() const 
    {
        return (_maxSpeed * _maxSpeed) >= (getSpeedSq());
    }

    double MovingEntity::getSpeed() const 
    {
        return glm::length(_velocity);
    }

    double MovingEntity::getSpeedSq() const 
    {
        return glm::length2(_velocity);
    }

    double MovingEntity::getMaxSpeed() const 
    {
        return _maxSpeed;
    }

    void MovingEntity::setMaxSpeed(double max) 
    {
        _maxSpeed = max;
    }

    double MovingEntity::getMaxForce() const 
    {
        return _maxForce;
    }

    void MovingEntity::setMaxForce(double max) 
    {
        _maxForce = max;
    }

    double MovingEntity::getMaxTurnRate() const 
    {
        return _maxTurnRate;
    }

    void MovingEntity::setMaxTurnRate(double max) 
    {
        _maxTurnRate = max;
    }
}