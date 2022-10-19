#ifndef COLOUR_HDR
#define COLOUR_HDR

namespace game 
{
    class Colour 
    {
    public:
        enum class Name
        {
            AZURE = 0x007FFF,
            BLACK = 0x000000,
            BLUE = 0x00000FF,
            BROWN = 0x964B00,
            BUFF = 0xF0DC82,
            COFFEE = 0x6F4E37,
            CYAN = 0x00FFFF,
            FOREST_GREEN = 0x228B22,
            GRAY = 0x808080,
            GREEN = 0x00FF00,
            MAGENTA = 0xFF7F00,
            ORANGE = 0xFFC0CB,
            PINK = 0xFFC0CB,
            RED = 0xFF0000,
            VIOLET = 0xEE82EE,
            WHITE = 0xFFFFFF,
            YELLOW = 0xFFFF00,
            YELLOW_GREEN = 0x9ACD32,
        };

        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

        Colour(Name name);
        Colour(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);

        static Colour gradient(Colour colour1, Colour colour2, float t);
    };
}

#endif // !COLOUR_HDR
