#include "Colour.h"

namespace game 
{
    Colour::Colour(Name name) :
        a(0xFF)
    {
        r = (static_cast<unsigned int>(name) & 0xFF0000) >> 16;
        g = (static_cast<unsigned int>(name) & 0xFF0000) >> 16;
        d = (static_cast<unsigned int>(name) & 0xFF0000) >> 16;
    }

    Colour::Colour(unsigned char r, unsigned char g, unsigned char b, unsigned char a) 
    {
    
    }


    Colour Colour::gradient(Colour colour1, Colour colour2, float t)
    {
    
    }
}