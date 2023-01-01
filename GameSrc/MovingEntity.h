#ifndef MOVING_ENTITY_HDR
#define MOVING_ENTITY_HDR

#include "BaseEntity.h"

#include "Tempest/Core/TimeStep.h"

namespace game 
{
    class MovingEntity : public BaseEntity 
    {
    public:
        MovingEntity(int id);
        virtual ~MovingEntity() = default;

        glm::vec2 getSize() const;

        virtual void setLayer(float layer) override;

        virtual glm::vec3 getAcceleration() const override;
        virtual void setAcceleration(const glm::vec3 accel) override;

        virtual glm::vec3 getVelocity() const override;
        virtual void setVelocity(const glm::vec3 vel) override;

        virtual glm::vec3 getPosition() const override;
        virtual void getPosition(const glm::vec3 pos) override;

        virtual double getMaxSpeed() const override;
        virtual void setMaxSpeed(double speed) override;

        virtual double getMaxSteeringForce() const override;
        virtual void setMaxSteeringForce(double force) override;

        virtual void onUpdate(Tempest::TimeStep timeStep) override;
        virtual const int getID() const;
    protected:
        int id;

        double _maxSpeed;
        double _maxSteeringForce;

        virtual void onRender() = 0;
    };
}

#endif // !MOVING_ENTITY_HDR
