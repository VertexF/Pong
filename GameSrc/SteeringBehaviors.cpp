#include "SteeringBehaviors.h"

#include <Tempest.h>

#include "Global.h"

namespace game
{
    //We keep track of the entity that is tired to the steering force via int id's
    SteeringBehaviors::SteeringBehaviors(int id) : _entityID(id),
                        _steeringForce(0.0, 0.0, 0.0), _target(0.0, 0.0, 0.0),
                       _summingMethods(SummingMethods::PRIORITIZED), 
                        _weightSeek(1.0)
    {
        //NOTE: Weighted values come from the params.ini file.
    }

    glm::vec3 SteeringBehaviors::calculate()
    {
        //Resets the steering force so the calculate functions below are working with a clear vector.
        _steeringForce = glm::vec3(0.0, 0.0, 0.0);

        switch (_summingMethods) 
        {
        case SummingMethods::WEIGHTED_AVERAGE:
            _steeringForce = calculateWeightedSum();
        case SummingMethods::PRIORITIZED:
            _steeringForce = calculatePrioritised();
        case SummingMethods::DITHERED:
            _steeringForce = calculateDithered();
        }

        return _steeringForce;
    }

    double SteeringBehaviors::forwardComponents()
    {
        return 0.0;
    }

    double SteeringBehaviors::sideComponents() 
    {
        return 0.0;
    }

    void SteeringBehaviors::setTarget(const glm::vec3 &target) 
    {
        _target = target;
    }

    glm::vec3 SteeringBehaviors::getForce() const 
    {
        return _steeringForce;
    }

    //All calculation functions are only interested in seek On
    glm::vec3 SteeringBehaviors::calculateWeightedSum() 
    {
        if (Tempest::Input::isMouseButtonPressed(0) == true)
        {
            glm::vec3 newTarget(Tempest::Input::getMousePosition(), 0.0);
            glm::vec3 force = seek(newTarget);
            force *= _weightSeek;
            _steeringForce += force;

            return _steeringForce;
        }
    }

    glm::vec3 SteeringBehaviors::calculatePrioritised() 
    {
        if (Tempest::Input::isMouseButtonPressed(0) == true)
        {
            glm::vec3 newTarget(Tempest::Input::getMousePosition(), 0.0);
            glm::vec3 force = seek(newTarget);
            force *= _weightSeek;
            force += force;

            if (accumulateForce(_steeringForce, force) == false)
            {
                return _steeringForce;
            }
        }

        return _steeringForce;
    }

    glm::vec3 SteeringBehaviors::calculateDithered() 
    {
        //Extra work is needed to scale the weight by a value
        if (Tempest::Input::isMouseButtonPressed(0) == true)
        {
            glm::vec3 newTarget(Tempest::Input::getMousePosition(), 0.0);
            glm::vec3 force = seek(newTarget);
            force *= _weightSeek;
            _steeringForce += force;

            if (_steeringForce.length() > glm::epsilon<float>())
            {
                if (_steeringForce.length() > ENTITY_MANAGER.get(_entityID)->getMaxSpeed()) 
                {
                    _steeringForce = glm::normalize(_steeringForce);
                    _steeringForce *= _steeringForce;
                }
            }

            return _steeringForce;
        }
    }

    //This function calculates how much of it's max steering force the vehicle has left to apply and applies that amount of the force.
    bool SteeringBehaviors::accumulateForce(glm::vec3& runningTotal, const glm::vec3& forceToAdd) 
    {
        double magnitudeSoFar = runningTotal.length();

        //calculates how much steering force remains to be used by the entity.
        double magnitudeLeft = ENTITY_MANAGER.get(_entityID)->getMaxSteeringForce() - magnitudeSoFar;

        //Nothing left to do.
        if (magnitudeLeft <= glm::epsilon<double>())
        {
            return false;
        }

        //Calculate the magitude of the force we want to add.
        double magnitudeToAdd = forceToAdd.length();

        if (magnitudeToAdd < magnitudeLeft) 
        {
            runningTotal += forceToAdd;
        }
        else 
        {
            glm::vec3 newForce = glm::normalize(forceToAdd);
            newForce *= magnitudeLeft;
            runningTotal += newForce;
        }

        return true;
    }

    glm::vec3 SteeringBehaviors::seek(const glm::vec3& target) 
    {
        glm::vec3 desiredVelocity = glm::normalize(target - ENTITY_MANAGER.get(_entityID)->getPosition());
        desiredVelocity *= ENTITY_MANAGER.get(_entityID)->getMaxSpeed();

        return (desiredVelocity - ENTITY_MANAGER.get(_entityID)->getVelocity());
    }
}