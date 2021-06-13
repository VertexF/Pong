#include "TextTest.h"

#include <stdio.h>
#include <string>

namespace game 
{
    TextTest::TextTest()
    {
    }

    TextTest::~TextTest()
    {
        if (_ttfBuffer != nullptr) 
        {
            delete[] _ttfBuffer;
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