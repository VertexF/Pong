#include "ResourceManager.h"

#include <exception>

#include <rapidxml_utils.hpp>
#include <Tempest.h>

#include "Background.h"
#include "Global.h"
#include "LevelTheme.h"

namespace 
{
    //Might be worth using a resource CMAKE thing instead of this.
    //MAJOR ISSUE! This only support textures right now!
    std::string getResourceFileName(const std::string& relativeFileName) 
    {
        return "Assets/Textures/" + relativeFileName;
    }
}

namespace game 
{
    //------------------Public Functions--------------------------------------
    ResourceManager::ResourceManager() :
        _isMainResourceManager(true),
        _parent(std::make_unique<ResourceManager>())
    {
    }

    ResourceManager::ResourceManager(const std::shared_ptr<ResourceManager>& parent) :
        _isMainResourceManager(false)
    {
        //We need to copy around the parent because multiple groups will come from the same parent.
        _parent = parent;
    }

    ResourceManager::~ResourceManager() 
    {
        TEMPEST_INFO("Release all resources");
        for (auto resource : _resources) 
        {
            switch (resource.second.type) 
            {
            case RESOURCE_BACKGROUND:
                delete resource.second.background;
                break;
            case RESOURCE_LEVELTHEME:
                delete resource.second.levelTheme;
                break;
            }
        }
    }

    const Background* ResourceManager::getBackground(const std::string& name) const 
    {
        const ResourceManager::Resource* resource = std::move(getResource(name));
        if (resource == nullptr || resource->type != RESOURCE_BACKGROUND)
        {
            TEMPEST_INFO("Warning resource not found {0} is return a nullptr", name);
            return nullptr;
        }
        return resource->background;
    }

    const LevelTheme* ResourceManager::getLevelTheme(const std::string& name) const 
    {
        const ResourceManager::Resource* resource = std::move(getResource(name));
        if (resource == nullptr || resource->type != RESOURCE_LEVELTHEME)
        {
            TEMPEST_INFO("Warning resource not found {0} is return a nullptr", name);
            return nullptr;
        }
        return resource->levelTheme;
    }

    const std::vector<std::shared_ptr<LevelTheme>> ResourceManager::getLevelThemes() const 
    {
        return _levelTheme;
    }

    const std::shared_ptr<ResourceManager> ResourceManager::getResourceGroup(const std::string& name) const
    {
        auto it = _groups.find(name);
        if(it == _groups.end())
        {
            TEMPEST_INFO("Warning resource group {0} is not found.", name);
            return nullptr;
        }
        return std::make_shared<ResourceManager>(it->second);
    }

    //This is the entry point of loading the XML file
    void ResourceManager::loadResources(const std::string& resourceFileName) 
    {
        //Only the root level resource manager can load resources
        assert(_isMainResourceManager);

        //Load the main resource file
        loadResourcesFromFile(resourceFileName);

        //TODO: Do you need to add stuff before if you are only loading backgrounds?
    }

    //------------------Private Functions--------------------------------------
    ResourceManager::ResourceManager(const ResourceManager& parent) 
    {
    }

    const ResourceManager::Resource* ResourceManager::getResource(const std::string& name) const
    {
        auto it = _resources.find(name);
        if (it == _resources.end() && _parent == nullptr)
        {
            return nullptr;
        }
        else if (_parent != nullptr)
        {
            _parent->getResource(name);
        }
        else
        {
            return &it->second;
        }
    }

    void ResourceManager::loadBackgrounds(rapidxml::xml_node<>* root)
    {
        //Enumerate backgrounds
        TEMPEST_INFO("Loading backgrounds...");

        for (rapidxml::xml_node<>* node = root->first_node("background"); node != nullptr; node->next_sibling("background"))
        {
            //Check that it has and id
            rapidxml::xml_attribute<>* idAttr = node->first_attribute("id");
            if (idAttr == nullptr) 
            {
                TEMPEST_WARN("Ignoring a background that did not have an id attribute");
                continue;
            }

            //Check for duplicates
            auto it = _resources.find(idAttr->value());
            if (it != _resources.end()) 
            {
                TEMPEST_WARN("Duplicate resource {0} found. It will be ignored.", idAttr->value());
                continue;
            }

            //Check if it has a tiling specified
            rapidxml::xml_attribute<>* tilingAttr = node->first_attribute("tiling");
            Background::BackgroundTiling tiling = Background::BackgroundTiling::BACKGROUND_HORIZONTAL;
            if (tilingAttr != nullptr) 
            {
                if (std::strcmp(tilingAttr->value(), "horizontal") == 0)
                {
                    tiling = Background::BackgroundTiling::BACKGROUND_HORIZONTAL;
                }
                else if (std::strcmp(tilingAttr->value(), "vertical") == 0)
                {
                    tiling = Background::BackgroundTiling::BACKGROUND_VERTICAL;
                }
                else if (std::strcmp(tilingAttr->value(), "all") == 0)
                {
                    tiling = Background::BackgroundTiling::BACKGROUND_ALL;
                }
                else 
                {
                    TEMPEST_WARN("Background resource {0} has invalid tiling attribute value {1}. Ingoring and using default value of horizontal.", idAttr->value(), tilingAttr->value());
                }
            }

            //Skipping everything else that turns up in the frame tag apart from the texture image location.
            std::string textureName;
            for (rapidxml::xml_node<>* frameNode = node->first_node("frame"); frameNode != nullptr; frameNode->next_sibling("frame"))
            {
                rapidxml::xml_attribute<>* imageAttr = frameNode->first_attribute("image");
                if (imageAttr != nullptr) 
                {
                    textureName = getResourceFileName(imageAttr->value());
                    //We CANNOT handle animation at all, concepts like frames need to added into the game engine later.
                    //EVERY background is just a static background picture.
                    break;
                }
                else 
                {
                    TEMPEST_WARN("Ignore a background frame resource as {0} did not have a valid path to a texture.", idAttr->value() );
                }
            }

            Background* background = new Background(textureName);
            Resource resource;
            resource.type = RESOURCE_BACKGROUND;
            resource.background = background;
            _resources[idAttr->value()] = resource;

            TEMPEST_INFO("Loaded background {0}", idAttr->value());
        }
    }

    void ResourceManager::loadLevelThemes(rapidxml::xml_node<>* root)
    {
    }

    void ResourceManager::loadGroups(rapidxml::xml_node<>* root)
    {
        //Enumerate group
        for (rapidxml::xml_node<>* node = root->first_node("group"); node != nullptr; node->next_sibling("group"))
        {
            rapidxml::xml_attribute<>* idAttr = node->first_attribute("id");
            if (idAttr == nullptr)
            {
                TEMPEST_WARN("Ignoring a resource group that did not have an id attribute.");
                continue;
            }
            std::string name = idAttr->value();

            //Check that the parent resource manager exists.
            rapidxml::xml_attribute<>* parentAttr = node->first_attribute("parent");
            std::shared_ptr<ResourceManager> parent;
            if (parentAttr != nullptr)
            {
                auto it = _groups.find(parentAttr->value());
                if (it != _groups.end()) 
                {
                    parent = it->second;
                }
                else 
                {
                    TEMPEST_WARN("Attempted to add a resource group {0} with parent {1} which did not exist. The group will not be added.", name, parentAttr->value());
                    continue;
                }
            }

            auto it = _groups.find(name);
            if (it != _groups.end()) 
            {
                TEMPEST_WARN("Attempted to add a resource group to a name that was already being used {0}. Any resources mapped by the resource group will not available.", name);
                continue;
            }

            std::shared_ptr<ResourceManager> group = std::make_shared<ResourceManager>(*parent);
            _groups.insert(it, std::pair<std::string, std::shared_ptr<ResourceManager>>(name, group));

            //Add all the key-value pairs to the child
            for (rapidxml::xml_node<>* res = node->first_node("resource"); res != nullptr; res = node->next_sibling("resource"))
            {
                //Check that is has a key-value pair specified
                rapidxml::xml_attribute<>* keyAttr = res->first_attribute("key");
                rapidxml::xml_attribute<>* valueAttr = res->first_attribute("value");
                rapidxml::xml_attribute<>* animationAttr = res->first_attribute("animation");
                rapidxml::xml_attribute<>* indexAttr = res->first_attribute("index");
                if (keyAttr == nullptr || (valueAttr == nullptr && (animationAttr == nullptr || indexAttr == nullptr))) 
                {
                    TEMPEST_WARN("Resource group {0} had an invalid key-value pair specified. It will be ignored", name);
                    continue;
                }

                //NOTE! Animation, Tiles Music and Sounds are all missing group from the main resource XML file.
                //Re-add them as you go. 

                //Check that the key is unique and that the value exists
                std::string key = keyAttr->value();
                auto it = group->_resources.find(key);
                if (it != group->_resources.end()) 
                {
                    TEMPEST_WARN("Resource group {0} specified a key that was already in use {1}", name, key);
                    continue;
                }

                if (valueAttr != nullptr) 
                {
                    std::string value = valueAttr->value();
                    it = _resources.find(value);
                    if (it == _resources.end()) 
                    {
                        TEMPEST_WARN("Resource group {0} specified a value for a resource that does not exist: {1}", name, value);
                        continue;
                    }

                    //Create the link to the resource
                    const Resource* resource = getResource(value);
                    Resource newResource(*resource);
                    group->_resources[key] = newResource;

                    TEMPEST_INFO("Added resource key-value pair: {0} -> {1}", key, value);
                }
                else 
                {
                    //IMPLEMENT WITH ANIMATIONED AND TILES.
                }
            }

            TEMPEST_INFO("Added resource group {0}", name);
        }
    }

    void ResourceManager::loadResourcesFromFile(const std::string& fileName) 
    {
        assert(_isMainResourceManager);

        TEMPEST_INFO("Loading resource from file {0}", fileName);

        //Parse the XML document.
        rapidxml::xml_document<> document;
        rapidxml::file xmlFile(fileName.c_str());
        document.parse<0>(xmlFile.data());
        rapidxml::xml_node<>* root = document.first_node();

        //Load any resource file imports specified in the file.
        for (rapidxml::xml_node<>* node = root->first_node("import"); node != nullptr; node = node->next_sibling("import"))
        {
            rapidxml::xml_attribute<>* fileAttr = node->first_attribute("file");
            if (fileAttr == nullptr) 
            {
                //There isn't a file to load.
                continue;
            }

            std::string fileName = getResourceFileName(fileAttr->value());
            try 
            {
                loadResourcesFromFile(fileName);
            }
            catch (const std::exception &e) 
            {
                TEMPEST_ERROR("Failed to load resources from file {0} The expection reads {1}", fileName, e.what());
            }
        }

        loadBackgrounds(root);
        loadGroups(root);
        loadLevelThemes(root);

        TEMPEST_INFO("Finished loading resources from file {0}", fileName);
    }
}