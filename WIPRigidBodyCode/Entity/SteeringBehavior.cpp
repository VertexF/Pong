#include "SteeringBehavior.h"

#include <memory>

namespace Tempest 
{
    SteeringBehavior::SteeringBehavior()
    {
    }

    glm::vec3 SteeringBehavior::seek(const glm::vec3& targetPosition, const glm::vec3& oldPosition, const glm::vec3& oldVelocity, float maxSpeed) 
    {
        glm::vec3 desired = glm::normalize(targetPosition - oldPosition); //* maxSpeed;

        return desired - oldVelocity;
    }
}