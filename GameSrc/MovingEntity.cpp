#include "MovingEntity.h"

namespace
{
    //TODO: Make this more accessable
    const double LINEAR_DAMPING = 0.98;
}

namespace game 
{
    //Max speed needs to be an input variable.
    MovingEntity::MovingEntity(int id) : BaseEntity(), id(id), _maxSpeed(70.0), _maxSteeringForce(150.0)
    {
    }

    glm::vec2 MovingEntity::getSize() const 
    {
        return size;
    }

    void MovingEntity::setLayer(float layer) 
    {
        position.z = layer;
    }

    glm::vec3 MovingEntity::getAcceleration() const
    {
        return acceleration;
    }

    void MovingEntity::setAcceleration(const glm::vec3 accel) 
    {
        acceleration = accel;
    }

    void MovingEntity::setVelocity(const glm::vec3 vel) 
    {
        velocity = vel;
    }

    glm::vec3 MovingEntity::getVelocity() const
    {
        return velocity;
    }

    glm::vec3 MovingEntity::getPosition() const 
    {
        return position;
    }

    void MovingEntity::getPosition(const glm::vec3 pos) 
    {
        position = pos;
    }

    double MovingEntity::getMaxSpeed() const 
    {
        return _maxSpeed;
    }

    void MovingEntity::setMaxSpeed(double speed) 
    {
        _maxSpeed = speed;
    }

    double MovingEntity::getMaxSteeringForce() const
    {
        return _maxSteeringForce;
    }

    void MovingEntity::setMaxSteeringForce(double force)
    {
        _maxSteeringForce = force;
    }

    void MovingEntity::onUpdate(Tempest::TimeStep timeStep) 
    {
        //TODO: Add angular acceleration.
        velocity += acceleration * timeStep.getSeconds();

        //Linear damping to slow everything down by a factor.
        velocity *= glm::pow(LINEAR_DAMPING, timeStep.getSeconds());

        position += velocity * timeStep.getSeconds();
    }

    const int MovingEntity::getID() const
    {
        return id;
    }

}