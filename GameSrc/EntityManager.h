#ifndef ENTITY_MANAGER_HDR
#define ENTITY_MANAGER_HDR

#include <map>
#include <memory>
#include <vector>

#include "BaseEntity.h"

namespace game 
{
    class EntityManager 
    {
    public:
        enum class EntityType 
        {
            VECHICLE,
            TOTAL_ENTITIES
        };
    public:
        EntityManager() = default;

        int instantiate(EntityType type);

        std::shared_ptr<BaseEntity> get(int id);

        void remove(int id);
    private:
        std::unordered_map<int, std::shared_ptr<BaseEntity>> _entities;

        std::vector<std::unique_ptr<BaseEntity>> _tester;
    };
}

#endif // !ENTITY_MANAGER_HDR
