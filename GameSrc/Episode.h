#ifndef EPISODE_HDR
#define EPISODE_HDR

#include <map>
#include <memory>

namespace game 
{
    class Level;
    class LevelGenerator;
    struct LevelTheme;

    //A playable episode of the game consisting of Levels the class and Maps.
    class Episode
    {
    public:
        ~Episode();

        //Creates level and ties it to this episode.
        void addGameLevel(int levelID, Level level);

        //Get a Level from the Episode by it's ID
        const Level* getGameLevel(int levelID) const;
    private:
        std::map<int, std::unique_ptr<Level>> levels;
    };
}

#endif // !EPISODE_HDR
