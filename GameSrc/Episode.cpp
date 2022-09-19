#include "Episode.h"

#include "Level.h"

namespace game
{
    Episode::~Episode() 
    {
    
    }

    //Creates level and ties it to this episode.
    void Episode::addGameLevel(int levelID, const std::shared_ptr<Level>& level)
    {
        std::map<int, std::shared_ptr<Level>>::iterator it = levels.find(levelID);
        if (it == levels.end())
        {
            levels.insert(std::make_pair(levelID, level));
        }
    }

    //Get a Level from the Episode by it's ID
    const std::shared_ptr<Level> Episode::getGameLevel(int levelID) const 
    {
        std::map<int, std::shared_ptr<Level>>::const_iterator it = levels.find(levelID);
        if (it != levels.end()) 
        {
            return it->second;
        }
    }
}