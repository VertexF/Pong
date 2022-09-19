#ifndef GAME_SESSION_HDR
#define GAME_SESSION_HDR

#include <memory>

#include "World.h"
#include "Episode.h"
//class Player;

namespace game 
{
    struct GameSession 
    {
    public:
        GameSession() 
        {
            world = std::make_unique<World>();
            episode = std::make_unique<Episode>();
        }

        std::unique_ptr<World> world;
        std::unique_ptr<Episode> episode;
        //std::unique_ptr<Player> player;
    };
}

#endif // !GAME_SESSION_HDR
