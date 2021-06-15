#include "TextTest.h"

#include <stdio.h>
#include <string>

#include "Tempest.h"

namespace game 
{
    TextTest::TextTest(float fontSize) : _fontSize(fontSize)
    {
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
        FILE* ttfFile = nullptr;
        if (fopen_s(&ttfFile, "Assets\\Fonts\\OpenSans-Regular.ttf", "rb") == 0)
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
        _fontInfo = std::make_unique<stbtt_fontinfo>();
        _asciiBuffer = new stbtt_packedchar[ASCII_BUFFER];

        if (stbtt_InitFont(_fontInfo.get(), _ttfBuffer, 0) == 0)
        {
            delete[] _ttfBuffer;
            TEMPEST_ERROR("Failed to started up STB_TTF");
        }

        // fill bitmap atlas with packed characters
        unsigned char* bitmap = nullptr;
        while (true) 
        {
            bitmap = new unsigned char[_textureSize * _textureSize];
            stbtt_pack_context packContext;
            stbtt_PackBegin(&packContext, bitmap, _textureSize, _textureSize, 0, 1, 0);
            stbtt_PackSetOversampling(&packContext, 1, 1);

            if (stbtt_PackFontRange(&packContext, _ttfBuffer, 0, _fontSize, 32, ASCII_BUFFER, _asciiBuffer) == false)
            {
                delete[] bitmap;
                stbtt_PackEnd(&packContext);
                _textureSize *= 2;
            }
            else 
            {
                stbtt_PackEnd(&packContext);
                break;
            }
        }

        //Remember the _textureSize * _textureSize is the texture size and sizeof(uint32_t) is the channel RGBA
        uint32_t* pixels = new uint32_t[_textureSize * _textureSize * sizeof(uint32_t)];

        for (int i = 0; i < _textureSize * _textureSize; ++i)
        {
            pixels[i] = 0xFFFFFF00 + bitmap[i];
        }
        
        _textTexture = Tempest::Texture2D::create(_textureSize, _textureSize);
        _textTexture->setData(pixels, (_textureSize * _textureSize * sizeof(uint32_t)));

    }

    void TextTest::onRender() 
    {
        Tempest::Renderer2D::drawQuad({ 0.f, 5.f, 0.0f }, { 10.f, 10.f }, _textTexture);
    }

    void TextTest::displayText(float x, float y, char* text)
    {
        for(int i = 0; text[i]; ++i)
        {
            if (text[i] >= 32 && text[i] < 128)
            {
                //stbtt_aligned_quad textureCoords;
                //stbtt_GetBakedQuad(_asciiBuffer[text[i] - 32], BITMAP_CHAR, BITMAP_CHAR, *text - 32, &x, &y, &textureCoords, 1);
                stbtt_packedchar* info = &_asciiBuffer[text[i] - 32];

                glm::vec4 texCoords = { info->x0, info->y0, info->x1, info->y1 };
                //SDL_Rect dst_rect = { x + info->xoff, y + info->yoff, info->x1 - info->x0, info->y1 - info->y0 };

                Tempest::Renderer2D::drawText({ x + info->xoff, y + info->yoff }, { 1.f, 1.f }, texCoords, _textTexture);
            }
        }

        Tempest::Renderer2D::drawQuad({ x, y }, { 1.f, 1.f }, _textTexture);
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

            if (stbtt_InitFont(_fontInfo.get(), _ttfBuffer, offsetIndexValue) == 1)
            {
                float ttfScale = stbtt_ScaleForPixelHeight(_fontInfo.get(), charSize);
                for (int textIter = 0; textIter < text.size(); ++textIter)
                {
                    unsigned short currectCaracter = text.at(textIter);
                    unsigned char* bitmap = stbtt_GetCodepointBitmap(_fontInfo.get(), 0, ttfScale, currectCaracter, &_charWidth, &_charHeight, 0, 0);

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