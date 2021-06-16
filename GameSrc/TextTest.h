#ifndef TEXT_TEST_HDR
#define TEXT_TEST_HDR

#include "stb_truetype.h"
#include "stb_rect_pack.h"

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
        TextTest(float fontSize);
        ~TextTest();

        //TODO : remove once you have built the OpenGL API structure for text.
        void printTextToConsole(std::string text, float charSize);

        void onRender();
        void displayText(float x, float y, char* text);
    private:
        void init();
        void TTFtoBitmap();

        unsigned char* _ttfBuffer;
        stbtt_packedchar* _asciiBuffer;

        int _charWidth = 0;
        int _charHeight = 0;

        uint32_t _textureSize = 32;
        float _fontSize;

        Tempest::ref<Tempest::Texture2D> _textTexture;

        Tempest::scope<stbtt_fontinfo> _fontInfo;
    };
}

#endif // !TEXT_TEST_HDR
