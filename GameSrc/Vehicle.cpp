#include "Vehicle.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/perpendicular.hpp>

namespace game 
{
    Vehicle::Vehicle(Tempest::scope<Tempest::GameWorld> world, const glm::vec3& pos, float rotation,
        const glm::vec3& velocity, float mass, float maxForce, float maxSpeed, float maxTurnRate,
        float scale) : 
        Tempest::MovingEntity(pos, scale, velocity, maxSpeed, glm::vec3(glm::sin(rotation), -glm::cos(rotation), 1.f),
            mass, glm::vec2(scale, scale), maxTurnRate, maxForce)
    {
    }

    void Vehicle::loadAssets() 
    {
    }

    void Vehicle::onUpdate(Tempest::TimeStep ts) 
    {
        intergrate(ts);
        //NOTE TODO: Add extra update code when needed.
    }

    void Vehicle::onRender() 
    {
        //Interface notes: I don't think the moving enitity should worry about scale because doesn't affect the maths of motion.
        Tempest::Renderer2D::drawRotatedQuad({ _pos.x, _pos.y, -0.5f }, { 1.f, 1.3f }, glm::radians(_), _shipTexture);
    }

    void Vehicle::onImGuiRender() 
    {
    }

    void Vehicle::reset() 
    {
    }

    bool Vehicle::handleMessage(const Tempest::Telegram& tele) 
    {
    }

    void Vehicle::write(std::ofstream outStream) 
    {
    }

    void Vehicle::read(std::ifstream inStream) 
    {
    }
}