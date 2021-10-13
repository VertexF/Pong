#include "BaseGameEntity.h"

namespace Tempest 
{
    void BaseGameEntity::setScale(const glm::vec2& value) 
    {
        _boundingRadius *= glm::max(value.x, value.y) / glm::max(_scale.x, _scale.y);
        _scale = value;
    }

    void BaseGameEntity::setScale(double value) 
    {
        _boundingRadius *= (value / glm::max(_scale.x, _scale.y));
        _scale = glm::vec2(value, value);
    }
}