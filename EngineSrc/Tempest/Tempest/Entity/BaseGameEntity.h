#ifndef BASE_GAME_ENTITY_HDR
#define BASE_GAME_ENTITY_HDR

#include "../Core/TimeStep.h"
#include <glm/glm.hpp>
#include <iostream>

namespace Tempest 
{
    struct Telegram;

    class BaseGameEntity
    {
    protected:
        //Its location in the enviroment.
        glm::vec3 _pos;
        glm::vec2 _scale;

        //The length of the object's bounding radius.
        double _boundingRadius;

        BaseGameEntity() : _id(nextValidID()),
            _boundingRadius(0.0),
            _pos(glm::vec3()),
            _scale(glm::vec2(1.0, 1.0)),
            _entityType(Default_Entity_Type),
            _tag(false)
        {
        }

        BaseGameEntity(int entityType) : _id(nextValidID()),
            _boundingRadius(0.0),
            _pos(glm::vec3()),
            _scale(glm::vec2(1.0, 1.0)),
            _entityType(entityType),
            _tag(false)
        {
        }

        BaseGameEntity(int entityType, glm::vec3 pos, double radius) :
            _id(nextValidID()),
            _boundingRadius(radius),
            _pos(pos),
            _scale(glm::vec2(1.0, 1.0)),
            _entityType(entityType),
            _tag(false)
        {
        }

        BaseGameEntity(int entityType, int forceID) :
            _id(forceID),
            _boundingRadius(0.0),
            _pos(glm::vec3()),
            _scale(glm::vec2(1.0, 1.0)),
            _entityType(entityType),
            _tag(false)
        {
        }
    public:
        virtual ~BaseGameEntity() = default;

        virtual void onUpdate(const TimeStep& time) = 0;
        virtual void onRender() = 0;

        virtual bool handleMessage(const Telegram& tele) = 0;

        virtual void write(std::ofstream outStream) = 0;
        virtual void read(std::ifstream inStream) = 0;

        glm::vec3 getPos() const { return _pos; }
        void setPos(const glm::vec3& pos) { _pos = pos; }

        double getBRadius() const { return _boundingRadius; }
        void setBRadius(double radius) { _boundingRadius = radius; }

        int getID() const { return _id; }

        bool isTagged() const { return _tag; }
        void tag() { _tag = true; }
        void untag() { _tag = false; }

        glm::vec2 getScale() const { return _scale; }
        void setScale(const glm::vec2& value);
        void setScale(double value);

        int getEntityType() const { return _entityType; }
        void setEntityType(int newType) { _entityType = newType; }
    public:
        enum { Default_Entity_Type = -1};

    private:
        int _id;
        //Every entity has a type associated with (health, troll, ammo).
        int _entityType;
        bool _tag;

        int nextValidID()
        {
            static int nextID = 0;
            return nextID++;
        }
    };
}

#endif // !BASE_GAME_ENTITY_HDR
