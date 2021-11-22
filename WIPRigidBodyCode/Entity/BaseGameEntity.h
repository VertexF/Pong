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
        //The length of the object's bounding radius.
        double _boundingRadius;

        BaseGameEntity();
        BaseGameEntity(int entityType);
        BaseGameEntity(int entityType, glm::vec3 pos, double radius);
        BaseGameEntity(int entityType, int forceID);

    public:
        virtual ~BaseGameEntity() = default;

        virtual void onUpdate(TimeStep time) = 0;

        virtual bool handleMessage(const Telegram& tele) = 0;

        virtual void write(std::ofstream outStream) = 0;
        virtual void read(std::ifstream inStream) = 0;

        double getBRadius() const;
        void setBRadius(double radius);

        int getID() const;

        bool isTagged() const;
        void tag();
        void untag();

        int getEntityType() const;
        void setEntityType(int newType);
    public:
        enum { Default_Entity_Type = -1};

    private:
        int _id;
        //Every entity has a type associated with (health, troll, ammo).
        int _entityType;
        bool _tag;
    };
}

#endif // !BASE_GAME_ENTITY_HDR
