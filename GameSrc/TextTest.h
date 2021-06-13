#ifndef TEXT_TEST_HDR
#define TEXT_TEST_HDR

#include "stb_truetype.h"
#include <string>

namespace game 
{
    class TextTest 
    {
    public:
        TextTest();
        ~TextTest();

        void printTextToConsole(std::string text, float charSize);
    private:
        stbtt_fontinfo _fontInfo;

        char unsigned* _ttfBuffer;

        int _charWidth = 0;
        int _charHeight = 0;
    };
}

#endif // !TEXT_TEST_HDR
