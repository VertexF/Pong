#ifndef TEXT_TEST_HDR
#define TEXT_TEST_HDR

#include "stb_truetype.h"
#include <string>

#include "Tempest/Renderer/Texture.h"

namespace 
{
    //These contain the size of the index buffers.
    const unsigned int BITMAP_CHAR = 512;
    const unsigned int BITMAP_BUFFER = BITMAP_CHAR * BITMAP_CHAR;
    const unsigned int ASCII_BUFFER = 96;
}

namespace game 
{
    class TextTest 
    {
    public:
        TextTest();
        ~TextTest();

        //TODO : remove once you have built the OpenGL API structure for text.
        void printTextToConsole(std::string text, float charSize);

        void onRender();
    private:
        void init();
        void TTFtoBitmap();

        stbtt_fontinfo _fontInfo;

        unsigned char* _ttfBuffer;
        unsigned char _characterBuffer[BITMAP_BUFFER];
        stbtt_bakedchar _asciiBuffer[ASCII_BUFFER];

        int _charWidth = 0;
        int _charHeight = 0;

        Tempest::ref<Tempest::Texture2D> _textTexture;
    };
}

#endif // !TEXT_TEST_HDR
