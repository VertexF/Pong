#include "PreComp.h"
#include "Vehicle.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/perpendicular.hpp>

namespace game 
{
    Vehicle::Vehicle(Tempest::ref<Tempest::GameWorld> world, const glm::vec3& pos, float rotation,
        const glm::vec3& velocity, float mass, float maxForce, float maxSpeed, float maxTurnRate,
        float scale) : 
        Tempest::MovingEntity(pos, scale, velocity, maxSpeed, glm::vec3(glm::sin(rotation), -glm::cos(rotation), 1.f),
            mass, glm::vec2(scale, scale), maxTurnRate, maxForce)
    {
    }

    void Vehicle::loadAssets() 
    {
        _shipTexture = Tempest::Texture2D::create("Assets/Textures/Triangle.png");
    }

    void Vehicle::onUpdate(Tempest::TimeStep ts) 
    {
        //NOTE TODO: Add extra update code when needed.

        if (Tempest::Input::isMouseButtonPressed(0)) 
        {
            rotateToFaceHeading(glm::vec3(Tempest::Input::getMousePosition(), 1.f));
        }

        intergrate(ts);
    }

    void Vehicle::onRender() 
    {
        //Interface notes: I don't think the moving enitity should worry about scale because doesn't affect the maths of motion.
        Tempest::Renderer2D::drawRotatedQuad(getTransform(), getScale(), _shipTexture);
    }

    void Vehicle::onImGuiRender() 
    {
    }

    void Vehicle::reset() 
    {
    }

    bool Vehicle::handleMessage(const Tempest::Telegram& tele) 
    {
        return false;
    }

    void Vehicle::write(std::ofstream outStream) 
    {
    }

    void Vehicle::read(std::ifstream inStream) 
    {
    }
}