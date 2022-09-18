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
        return "Assets/" + relativeFileName;
    }
}

namespace game 
{
    //------------------Public Functions--------------------------------------
    ResourceManager::ResourceManager() :
        _isMainResourceManager(true)
    {
    }

    ResourceManager::~ResourceManager() 
    {
    }

    const std::shared_ptr<Background> ResourceManager::getBackground(const std::string& name) const 
    {
        std::shared_ptr<ResourceManager::Resource> resource = getResource(name);
        if (resource == nullptr || resource->type != RESOURCE_BACKGROUND)
        {
            TEMPEST_INFO("Warning resource not found {0} is return a nullptr", name);
            return nullptr;
        }
        return resource->background;
    }

    const std::shared_ptr<LevelTheme> ResourceManager::getLevelTheme(const std::string& name) const
    {
        std::shared_ptr<ResourceManager::Resource> resource = getResource(name);
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
    ResourceManager::ResourceManager(const std::shared_ptr<ResourceManager>& parent) :
        _isMainResourceManager(false)
    {
        //We need to copy around the parent because multiple groups will come from the same parent.
        _parent = parent;
    }

    const std::shared_ptr<ResourceManager::Resource> ResourceManager::getResource(const std::string& name) const
    {
        auto it = _resources.find(name);
        if (it == _resources.end() && _parent == nullptr)
        {
            return nullptr;
        }
        else if (_parent != nullptr)
        {
            return _parent->getResource(name);
        }
        else
        {
            return it->second;
        }
    }

    void ResourceManager::loadBackgrounds(rapidxml::xml_node<>* root)
    {
        //Enumerate backgrounds
        TEMPEST_INFO("Loading backgrounds...");

        for (rapidxml::xml_node<>* node = root->first_node("background"); node != nullptr; node = node->next_sibling("background"))
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

            rapidxml::xml_attribute<>* timeAttr = node->first_attribute("time");
            int time = 1;
            if(timeAttr != nullptr) 
            {
                time = std::atoi(timeAttr->value());
            }

            //Skipping everything else that turns up in the frame tag apart from the texture image location.
            std::vector<Tempest::ref<Tempest::Texture2D>> _textures;
            std::string textureName;
            for (rapidxml::xml_node<>* frameNode = node->first_node("frame"); frameNode != nullptr; frameNode = frameNode->next_sibling("frame"))
            {
                rapidxml::xml_attribute<>* imageAttr = frameNode->first_attribute("image");
                if (imageAttr != nullptr) 
                {
                    textureName = getResourceFileName(imageAttr->value());
                    //We CANNOT handle animation at all, concepts like frames need to added into the game engine later.
                    //EVERY background is just a static background picture.
                    _textures.emplace_back(Tempest::Texture2D::create(textureName));
                }
                else 
                {
                    TEMPEST_WARN("Ignore a background frame resource as {0} did not have a valid path to a texture.", idAttr->value() );
                }
            }

            ////TexCoords
            //glm::vec2 coords = {0, 0};
            //glm::vec2 cellSize = {0, 0};
            ////TextureSize
            //glm::vec2 spriteSize = {0, 0};
            std::shared_ptr<Background> background = std::make_shared<Background>();
            for (auto texture : _textures)
            {
                background->addFrame(texture, { 0, 0 }, { texture->getWidth(), texture->getHeight() }, {1, 1}, time);
            }

            std::shared_ptr<Resource> resource = std::make_shared<Resource>();
            resource->type = RESOURCE_BACKGROUND;
            resource->background = background;
            _resources[idAttr->value()] = resource;

            TEMPEST_INFO("Loaded background {0}", idAttr->value());
        }
    }

    void ResourceManager::loadGroups(rapidxml::xml_node<>* root)
    {
        //Enumerate group
        TEMPEST_INFO("Loading Groups...");

        for (rapidxml::xml_node<>* node = root->first_node("group"); node != nullptr; node = node->next_sibling("group"))
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

            std::shared_ptr<ResourceManager> group = std::make_shared<ResourceManager>(parent);
            _groups.insert(it, std::pair<std::string, std::shared_ptr<ResourceManager>>(name, group));

            //Add all the key-value pairs to the child
            for (rapidxml::xml_node<>* res = node->first_node("resource"); res != nullptr; res = res->next_sibling("resource"))
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
                auto iter = group->_resources.find(key);
                if (iter != group->_resources.end()) 
                {
                    TEMPEST_WARN("Resource group {0} specified a key that was already in use {1}", name, key);
                    continue;
                }

                if (valueAttr != nullptr) 
                {
                    std::string value = valueAttr->value();
                    iter = _resources.find(value);
                    if (iter == _resources.end()) 
                    {
                        TEMPEST_WARN("Resource group {0} specified a value for a resource that does not exist: {1}", name, value);
                        continue;
                    }

                    //Create the link to the resource
                    const std::shared_ptr<Resource> resource = getResource(value);
                    std::shared_ptr<Resource> newResource = resource;
                    group->_resources[key] = newResource;

                    TEMPEST_INFO("Added resource key-value pair: {0} -> {1}", key, value);
                }
                else 
                {
                    //TODO:
                    //IMPLEMENT WITH ANIMATIONS AND TILES.
                }
            }

            TEMPEST_INFO("Added resource group {0}", name);
        }
    }

    void ResourceManager::loadLevelThemes(rapidxml::xml_node<>* root)
    {
        //Enumerate themes
        TEMPEST_INFO("Loading Themes...");
        for (rapidxml::xml_node<>* node = root->first_node("theme"); node != nullptr; node = node->next_sibling("theme"))
        {
            //Check that it has an id
            rapidxml::xml_attribute<>* idAttr = node->first_attribute("id");
            if (idAttr == nullptr) 
            {
                TEMPEST_WARN("Ingoring a theme that did not have an id attribute");
                continue;
            }

            //Check for duplicates
            auto it = _resources.find(idAttr->value());
            if (it != _resources.end()) 
            {
                TEMPEST_WARN("Duplicate resource {0} found. It will be ignored", idAttr->value());
                continue;
            }

            std::shared_ptr<LevelTheme> theme = std::make_shared<LevelTheme>();
            std::string name = idAttr->value();

            //Load entites. 
            //NOTE: This doesn't do anything right now but I will still build logic.
            for (rapidxml::xml_node<>* entity = node->first_node("entity"); entity != nullptr; entity = entity->next_sibling("entity"))
            {
                rapidxml::xml_attribute<>* id = entity->first_attribute("id");
                rapidxml::xml_attribute<>* group = entity->first_attribute("group");

                if (id == nullptr || group == nullptr) 
                {
                    TEMPEST_WARN("Theme {0} had an entity specified without an id or group attribute. This theme will be ignored", name);
                    continue;
                }

                auto iter = _groups.find(group->value());
                if (iter == _groups.end()) 
                {
                    TEMPEST_WARN("Theme {0} had an entity with an invalid group named {1}. This theme will be ignored", name, group->value());
                    continue;
                }

                //Define the interface before you just uncomment this code and run with it.
                //ResourceManager* resourceGroup = it->second;
                //theme->addEntityType(id->value(), resourceGroup);
            }

            for (rapidxml::xml_node<>* entity = node->first_node("resource"); entity != nullptr; entity = entity->next_sibling("resource")) 
            {
                rapidxml::xml_attribute<>* id = entity->first_attribute("id");

                if (id == nullptr)
                {
                    TEMPEST_WARN("Theme {0} had an entity specified without an id or group attribute. This theme will be ignored", name);
                    continue;
                }

                const std::shared_ptr<Resource> resource = getResource(id->value());
                if (resource == nullptr)
                {
                    TEMPEST_WARN("Theme {0} had a resource with an invalid id specified {1}. This theme will be ignored", name, id->value());
                    continue;
                }

                if (resource->type == RESOURCE_BACKGROUND) 
                {
                    theme->appendBackgrounds(std::move(resource->background));
                }
                //ADD MUSIC HERE if else here.
                else 
                {
                    TEMPEST_WARN("Theme {0} had a resource {1} that wasn't a background or music", name, id->value());
                    continue;
                }

                //Check if a parent was specified
                rapidxml::xml_attribute<>* parentAttr = node->first_attribute("parent");
                if(parentAttr != nullptr)
                {
                    //Not tested parently
                    //Find the parent theme.
                    std::string parentName = parentAttr->value();
                    const std::shared_ptr<LevelTheme> parent = getLevelTheme(parentName);
                    if (parent == nullptr) 
                    {
                        TEMPEST_WARN("Theme {0} specified a parent theme {1} that did not exist.", name, parentName);
                    }
                    else 
                    {
                        //Find anything that the parent has that we don't have to copy it.
                        //theme->inherit(*parent);
                    }
                }
                else if (name.compare("default_theme") != 0)
                {
                    //By default inherit default_theme
                    //theme->inherit(*getLevelTheme("default_theme"));
                }
            }

            //Create the resource
            std::shared_ptr<Resource> resource = std::make_shared<Resource>();
            resource->type = RESOURCE_LEVELTHEME;
            resource->levelTheme = theme;
            _resources[name] = resource;
            _levelTheme.emplace_back(theme);

            TEMPEST_INFO("Loaded theme {0}.", name);
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
            rapidxml::xml_attribute<>* fileAttribute = node->first_attribute("file");
            if (fileAttribute == nullptr)
            {
                //There isn't a file to load.
                continue;
            }

            std::string recuriveFileName = getResourceFileName(fileAttribute->value());
            try 
            {
                loadResourcesFromFile(recuriveFileName);
            }
            catch (const std::exception &e) 
            {
                TEMPEST_ERROR("Failed to load resources from file {0} The expection reads {1}", recuriveFileName, e.what());
            }
        }

        loadBackgrounds(root);
        loadGroups(root);
        loadLevelThemes(root);

        TEMPEST_INFO("Finished loading resources from file {0}", fileName);
    }
}