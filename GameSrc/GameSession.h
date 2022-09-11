#ifndef GAME_SESSION_HDR
#define GAME_SESSION_HDR

#include <memory>

class World;
class Episode;
//class Player;

namespace game 
{
    struct GameSession 
    {
        std::unique_ptr<World> world;
        std::unique_ptr<Episode> episode;
        //std::unique_ptr<Player> player;
    };
}

#endif // !GAME_SESSION_HDR
