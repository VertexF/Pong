#ifndef STEERING_BEHAVIORS_HDR
#define STEERING_BEHAVIORS_HDR

#include <glm/glm.hpp>

namespace game 
{
    class SteeringBehaviors 
    {
    private:
        enum class SummingMethods 
        {
            WEIGHTED_AVERAGE,
            PRIORITIZED,
            DITHERED
        };

    public:
        SteeringBehaviors(int id);

        glm::vec3 calculate();
        double forwardComponents();
        double sideComponents();

        void setTarget(const glm::vec3 &target);

        glm::vec3 getForce() const;
    private:
        glm::vec3 calculateWeightedSum();
        glm::vec3 calculatePrioritised();
        glm::vec3 calculateDithered();

        bool accumulateForce(glm::vec3 &runningTotal, const glm::vec3 &forceToAdd);

        glm::vec3 seek(const glm::vec3 &target);

        int _entityID;

        //Resulting force from calucations
        glm::vec3 _steeringForce;
        glm::vec3 _target;

        SummingMethods _summingMethods;

        double _weightSeek;
    };
}

#endif // !STEERING_BEHAVIORS_HDR
