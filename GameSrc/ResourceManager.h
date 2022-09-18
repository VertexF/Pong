#ifndef RESOURCE_MANAGER_HDR
#define RESOURCE_MANAGER_HDR

#include <memory>
#include <map>
#include <string>
#include <rapidxml.hpp>

#include "Background.h"
#include "LevelTheme.h"

namespace game 
{
    class ResourceManager 
    {
    public:
        ResourceManager();
        ResourceManager(const std::shared_ptr<ResourceManager>& parent);

        ~ResourceManager();

        const std::shared_ptr<Background> getBackground(const std::string& name) const;
        const std::shared_ptr<LevelTheme> getLevelTheme(const std::string& name) const;
        const std::vector<std::shared_ptr<LevelTheme>> getLevelThemes() const;
        const std::shared_ptr<ResourceManager> getResourceGroup(const std::string& name) const;
        void loadResources(const std::string& resourceFileName);
    
    private:
        std::shared_ptr<ResourceManager> _parent;
        std::map<std::string, std::shared_ptr<ResourceManager>> _groups;

        enum ResourceType
        {
            RESOURCE_BACKGROUND,
            RESOURCE_LEVELTHEME
        };

        struct Resource
        {
            ResourceType type;

            std::shared_ptr<Background> background;
            std::shared_ptr<LevelTheme> levelTheme;
        };

        bool _isMainResourceManager;

        //COMPILATION ISSUE! UNIONS paired with shared_ptrs aren't playing nice.
        std::map<std::string, std::shared_ptr<Resource>> _resources;

        std::vector<std::shared_ptr<LevelTheme>> _levelTheme;

        const std::shared_ptr<ResourceManager::Resource> getResource(const std::string& name) const;

        void loadResourcesFromFile(const std::string& fileName);
        void loadBackgrounds(rapidxml::xml_node<>* root);
        void loadGroups(rapidxml::xml_node<>* root);
        void loadLevelThemes(rapidxml::xml_node<>* root);
    };
}

#endif // !RESOURCE_MANAGER_HDR
