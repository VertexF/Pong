#include "EntityManager.h"

#include "Vechicle.h"
#include <Tempest.h>

namespace game 
{
    int EntityManager::instantiate(EntityType type)
    {
        switch (type) 
        {
        case EntityType::VECHICLE:
            int ID = _entities.size();
            std::shared_ptr<Vechicle> vechicle = std::make_shared<Vechicle>(ID);
            _entities.insert(std::pair(ID, vechicle));
            return ID;
            break;
        }
    }

    std::shared_ptr<BaseEntity> EntityManager::get(int id)
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
        {
            return std::shared_ptr<BaseEntity>(it->second);
        }

        //This should be removed when I have a more complete system because this isn't an error.
        TEMPEST_ERROR("Debug only! This Entity with ID {0} does not exist.", id);
        return nullptr;
    }

    void EntityManager::remove(int id) 
    {
        auto it = _entities.find(id);
        if (it == _entities.end())
        {
            TEMPEST_ERROR("This Entity with ID {0} does not exist.", id);
        }
        else
        {
            _entities.erase(it);
        }
    }
}