#include "TextTest.h"

#include <stdio.h>
#include <string>

#include "Tempest.h"

namespace game 
{
    TextTest::TextTest()
    {
        _textTexture = Tempest::Texture2D::create(BITMAP_CHAR, BITMAP_CHAR, 1);

        init();
        TTFtoBitmap();
    }

    TextTest::~TextTest()
    {
        if (_ttfBuffer != nullptr) 
        {
            delete[] _ttfBuffer;
        }
    }

    void TextTest::init() 
    {
        FILE* ttfFile = fopen("Assets\\Fonts\\ShortBaby.ttf", "rb");

        if (ttfFile != nullptr)
        {
            fseek(ttfFile, 0, SEEK_END);
            long bufferSize = ftell(ttfFile); /* how long is the file ? */
            fseek(ttfFile, 0, SEEK_SET); /* reset */

            _ttfBuffer = new unsigned char[bufferSize];

            if (_ttfBuffer != nullptr)
            {
                if (fread_s(_ttfBuffer, bufferSize, bufferSize, 1, ttfFile) == 0)
                {
                    TEMPEST_ERROR("Failed to read from the loaded TTF file.");
                }
            }
            else
            {
                TEMPEST_ERROR("File appears to be empty");
            }

            fclose(ttfFile);
        }
        else 
        {
            TEMPEST_ERROR("Could not open TTF.");
        }
    }

    void TextTest::TTFtoBitmap() 
    {
        //We are restart afew, I think we might need to work out how wide and high the TTF characters, but for now we actually data.
        stbtt_BakeFontBitmap(_ttfBuffer, 0, 32.f, _characterBuffer, BITMAP_CHAR, BITMAP_CHAR, 32, ASCII_BUFFER, _asciiBuffer);

        if (_characterBuffer == nullptr)
        {
            TEMPEST_CRITICAL("Could not bake to bitmap font.");
        }

        _textTexture->setData(_characterBuffer, sizeof(_characterBuffer));
    }

    void TextTest::onRender() 
    {
        Tempest::Renderer2D::drawQuad({ 0.f, 5.f, 0.0f }, { 10.f, 10.f }, _textTexture);
    }

    void TextTest::displayText(float x, float y, char* text)
    {
        while (*text)
        {
            if (*text >= 32 && *text < 128)
            {
                stbtt_aligned_quad textureCoords;
                stbtt_GetBakedQuad(_asciiBuffer, BITMAP_CHAR, BITMAP_CHAR, *text - 32, &x, &y, &textureCoords, 1);

                Tempest::Renderer2D::drawText({ x - 64.f, y }, { 1.f, 1.f }, textureCoords, _textTexture);
            }

            ++text;
        }
    }

    void TextTest::printTextToConsole(std::string text, float charSize)
    {
        FILE* ttfFile = fopen("Assets\\Fonts\\OpenSans-Regular.ttf", "rb");

        fseek(ttfFile, 0, SEEK_END);
        long bufferSize = ftell(ttfFile); /* how long is the file ? */
        fseek(ttfFile, 0, SEEK_SET); /* reset */

        _ttfBuffer = new unsigned char[bufferSize];

        if (ttfFile != nullptr)
        {
            fread(_ttfBuffer, 1, bufferSize, ttfFile);
            fclose(ttfFile);

            int offsetIndexValue = stbtt_GetFontOffsetForIndex(_ttfBuffer, 0);

            if (stbtt_InitFont(&_fontInfo, _ttfBuffer, offsetIndexValue) == 1)
            {
                float ttfScale = stbtt_ScaleForPixelHeight(&_fontInfo, charSize);
                for (int textIter = 0; textIter < text.size(); ++textIter)
                {
                    unsigned short currectCaracter = text.at(textIter);
                    unsigned char* bitmap = stbtt_GetCodepointBitmap(&_fontInfo, 0, ttfScale, currectCaracter, &_charWidth, &_charHeight, 0, 0);

                    for (int j = 0; j < _charHeight; ++j)
                    {
                        for (int i = 0; i < _charWidth; ++i)
                        {
                            putchar(" .:ioVM@"[bitmap[j * _charWidth + i] >> 5]);
                        }

                        putchar('\n');
                    }
                }
            }
            else 
            {
                TEMPEST_ERROR("Error: Failed to initalised TTF file.");
            }
        }
        else 
        {
            TEMPEST_ERROR("Error: Could not load TTF file");
        }
    }
}