#include "BaseGameEntity.h"

namespace 
{
    static inline int nextValidID()
    {
        static int nextID = 0;
        return nextID++;
    }
}

namespace Tempest 
{
    BaseGameEntity::BaseGameEntity() : _id(nextValidID()),
        _boundingRadius(0.0),
        _entityType(Default_Entity_Type),
        _tag(false)
    {
    }

    BaseGameEntity::BaseGameEntity(int entityType) : _id(nextValidID()),
        _boundingRadius(0.0),
        _entityType(entityType),
        _tag(false)
    {
    }

    BaseGameEntity::BaseGameEntity(int entityType, glm::vec3 pos, double radius) :
        _id(nextValidID()),
        _boundingRadius(radius),
        _entityType(entityType),
        _tag(false)
    {
    }

    BaseGameEntity::BaseGameEntity(int entityType, int forceID) :
        _id(forceID),
        _boundingRadius(0.0),
        _entityType(entityType),
        _tag(false)
    {
    }

    double BaseGameEntity::getBRadius() const 
    { 
        return _boundingRadius; 
    }

    void BaseGameEntity::setBRadius(double radius) 
    { 
        _boundingRadius = radius; 
    }

    int BaseGameEntity::getID() const 
    { 
        return _id; 
    }

    bool BaseGameEntity::isTagged() const 
    { 
        return _tag; 
    }

    void BaseGameEntity::tag() 
    {
        _tag = true; 
    }

    void BaseGameEntity::untag() 
    {
        _tag = false; 
    }

    //void BaseGameEntity::setScale(const glm::vec2& value) 
    //{
    //    _boundingRadius *= glm::max(value.x, value.y) / glm::max(_scale.x, _scale.y);
    //    _scale = value;
    //}

    //void BaseGameEntity::setScale(double value) 
    //{
    //    _boundingRadius *= (value / glm::max(_scale.x, _scale.y));
    //    _scale = glm::vec2(value, value);
    //}

    int BaseGameEntity::getEntityType() const 
    { 
        return _entityType; 
    }

    void BaseGameEntity::setEntityType(int newType) 
    { 
        _entityType = newType; 
    }
}