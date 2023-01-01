#include "Vechicle.h"

#include "Global.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace game 
{
    Vechicle::Vechicle(int id) : MovingEntity(id)
    {
        loadTexture();
    }

    void Vechicle::loadTexture()
    {
        _arrowTexture = Tempest::Texture2D::create("Assets/Textures/Arrow.png");
    }

    void Vechicle::onRender()
    {
        Tempest::Renderer2D::drawRotatedQuad(position, size, 0, _arrowTexture);
    }

    void Vechicle::onUpdate(Tempest::TimeStep timeStep)
    {
        MovingEntity::onUpdate(timeStep);

        onRender();
    }
}