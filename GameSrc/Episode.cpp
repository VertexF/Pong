#include "Episode.h"

#include "Level.h"

namespace game
{
    Episode::~Episode() 
    {
    
    }

    //Creates level and ties it to this episode.
    void Episode::addGameLevel(int levelID, Level level)
    {
        std::map<int, std::unique_ptr<Level>>::iterator it = levels.find(levelID);
        if (it == levels.end())
        {
            levels.insert(std::make_pair(levelID, std::make_unique<Level>(level)));
        }
    }

    //Get a Level from the Episode by it's ID
    const Level* Episode::getGameLevel(int levelID) const 
    {
        std::map<int, std::unique_ptr<Level>>::const_iterator it = levels.find(levelID);
        if (it != levels.end()) 
        {
            return it->second.get();
        }
    }
}