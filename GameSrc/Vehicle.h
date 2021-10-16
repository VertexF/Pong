#ifndef VEHICLE_HDR
#define VEHICLE_HDR

#include <Tempest.h>
#include <glm/glm.hpp>

namespace game 
{
    class Vehicle : public Tempest::MovingEntity
    {
    public:
        Vehicle(Tempest::ref<Tempest::GameWorld> world, const glm::vec3& pos, float rotation,
            const glm::vec3& velocity, float mass, float maxForce, float maxSpeed, float maxTurnRate,
            float scale);

        virtual ~Vehicle() = default;

        void loadAssets();
        virtual void onUpdate(Tempest::TimeStep ts) override;
        virtual void onRender() override;

        void onImGuiRender();
        void reset();

        virtual bool handleMessage(const Tempest::Telegram& tele) override;

        virtual void write(std::ofstream outStream) override;
        virtual void read(std::ifstream inStream) override;
    private:
        Vehicle(const Vehicle& other) = default;
        Vehicle(Vehicle&& other) noexcept = default; 
        Vehicle& operator=(const Vehicle& other) = default;
        Vehicle& operator=(Vehicle&& other) noexcept = default;

        //NOTE! Smooth steering behavior hasn't been written.

        //This is so vehicles can access any obstacles, paths, wall or agent data.
        Tempest::ref<Tempest::GameWorld> _gameWorld;
        Tempest::scope<Tempest::SteeringBehavior> _steeringBehavior;

        Tempest::ref<Tempest::Texture2D> _shipTexture;

        float _time = 0.f;
    };
}

#endif // !VEHICLE_HDR
