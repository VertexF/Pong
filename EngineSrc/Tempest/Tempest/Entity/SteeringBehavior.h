#ifndef STEERING_BEHAVIOR_HDR
#define STEERING_BEHAVIOR_HDR

#include <glm/glm.hpp>

namespace Tempest 
{
    class SteeringBehavior 
    {
    public:
        SteeringBehavior();

        glm::vec3 seek(const glm::vec3& targetPosition, const glm::vec3& oldPosition, const glm::vec3& oldVelocity, float maxSpeed);
    };
}

#endif // !STEERING_BEHAVIOR_HDR
