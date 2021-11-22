#include "RigidBody.h"

#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

//NOTE! Scale is only and not calulated.

namespace Tempest 
{
    RigidBody::RigidBody(const glm::vec3& position, const glm::vec3& velocity,
                              float maxSpeed, const glm::vec3& heading, float mass,
                              const glm::vec2& scale, float turnRate, float maxForce) 
        _velocity(velocity),
                               _heading(heading),
                               _mass(mass),
                               _side(glm::perp(heading, glm::vec3(1.0, 0.0, 1.0))),
                               _maxSpeed(maxSpeed),
                               _maxTurnRate(turnRate),
                               _maxForce(maxForce),
                               _transformMatrix(1.f)
    {
        _scale = scale;
    }

    glm::vec3 RigidBody::getPosition() const 
    {
        return _position;
    }

    void RigidBody::setPosition(const glm::vec3& pos) 
    {
        _position = pos;
    }

    glm::vec3 RigidBody::getVelocity() const 
    {
        return _velocity;
    }

    void RigidBody::setVelocity(const glm::vec3& vel) 
    {
        _velocity = vel;
    }

    glm::vec3 RigidBody::getAcceleration() const
    {
        return _acceleration;
    }

    void RigidBody::setAcceleration(const glm::vec3& acc)
    {
        _acceleration = acc;
    }

    glm::vec2 RigidBody::getScale() const 
    {
        return _scale;
    }

    void RigidBody::setScale(const glm::vec2& value) 
    {
        _scale = value;
    }

    void RigidBody::setScale(float value) 
    {
        _scale = { value, value };
    }

    float RigidBody::getMass() const 
    {
        return _mass;
    }

    glm::vec3 RigidBody::getSide() const 
    {
        return _side;
    }

    glm::vec3 RigidBody::getHeading() const 
    {
        return _heading;
    }

    void RigidBody::setHeading(const glm::vec3& newHeading) 
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
    bool RigidBody::rotateToFaceHeading(const glm::vec3& target) 
    {
        glm::vec3 delta = target - _position;

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

    bool RigidBody::isSpeedMaxedOut() const 
    {
        return (_maxSpeed * _maxSpeed) >= (getSpeedSq());
    }

    float RigidBody::getSpeed() const 
    {
        return glm::length(_velocity);
    }

    float RigidBody::getSpeedSq() const 
    {
        return glm::length2(_velocity);
    }

    float RigidBody::getMaxSpeed() const 
    {
        return _maxSpeed;
    }

    void RigidBody::setMaxSpeed(float max) 
    {
        _maxSpeed = max;
    }

    float RigidBody::getMaxForce() const 
    {
        return _maxForce;
    }

    void RigidBody::setMaxForce(float max) 
    {
        _maxForce = max;
    }

    float RigidBody::getMaxTurnRate() const 
    {
        return _maxTurnRate;
    }

    void RigidBody::setMaxTurnRate(float max) 
    {
        _maxTurnRate = max;
    }

    glm::mat4 RigidBody::getTransform() const 
    {
        return _transformMatrix;
    }

    void RigidBody::intergrate(Tempest::TimeStep ts)
    {
        //glm::vec3 oldPos = getPos();
        //_forceAccumate = { 0.f, 0.f, 0.f }; //= _steeringBehavior->calculate();

        _lastFrameAcceleration = _acceleration;
        _lastFrameAcceleration = _lastFrameAcceleration + (_forceAccumate / _mass);

        _velocity = _velocity + (_lastFrameAcceleration * static_cast<float>(ts));
        _rotation = _rotation + (_angularAcceleration * static_cast<float>(ts));

        _velocity *= glm::pow(linearDamping, ts);
        _rotation *= glm::pow(angularDamping, ts);

        _position = _position + (_velocity * static_cast<float>(ts));

        //Add Scaled vector needs to be part of GLM library.
        glm::quat q(0.f, _rotation * static_cast<float>(ts));
        q *= _orientation;
        _orientation = _orientation + q * 0.5f;

        calculateTransformMatrix();

        clearAccumlator();

        ////Calculating drag force.
        //if (glm::length(_velocity) > _maxSpeed) 
        //{
        //    _velocity = glm::normalize(_velocity);
        //    _velocity *= _maxSpeed;
        //}

        //if (glm::epsilonEqual(glm::length2(_velocity), 0.f, 00000000001.f) == false)
        //{
        //    _heading = glm::normalize(_velocity);
        //    _side = glm::perp(_heading, glm::vec3(1.0, 0.0, 1.0));
        //}

        //wrapAround(_pos, 1.f, 1.f);

        //calculateTransformMatrix();
    }

    void RigidBody::clearAccumlator() 
    {
        _forceAccumate = { 0.f, 0.f, 0.f };
        _torqueAccumate = { 0.f, 0.f, 0.f }
    }

    void RigidBody::calculateTransformMatrix()
    {
        _transformMatrix = glm::translate(glm::mat4x4(1.f), _position) * glm::toMat4(_orientation);

        _transformMatrix = glm::inverse(_transformMatrix);
    }
}