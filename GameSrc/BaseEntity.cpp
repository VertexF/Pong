#include "BaseEntity.h"

namespace game
{
    BaseEntity::BaseEntity() : position(0.0, 0.0, 0.0), size(1.0, 1.0), acceleration(0.0, 0.0, 0.0), velocity(0.0, 0.0, 0.0), layer(1.f)
    {
    }

    double BaseEntity::getAge() const 
    {
        //TODO: Might need to implement this.
        return 0;
    }

    void BaseEntity::setOrientation(Direction direction) 
    {
        //TODO: Check this is needed.
        switch (direction) 
        {
        case Direction::UP:
            break;
        case Direction::DOWN:
            break;
        case Direction::LEFT:
            break;
        case Direction::RIGHT:
            break;
        }
    }
}