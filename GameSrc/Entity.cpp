#include "Entity.h"

namespace game
{
    Entity::Entity()
    {
    }

    double Entity::getAge() const 
    {
        //TODO: Might need to implement this.
        return 0;
    }

    void Entity::setOrientation(Direction direction) 
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