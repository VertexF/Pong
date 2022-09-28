#include "PreComp.h"
#include "OpenGLTexture.h"

namespace Tempest 
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, uint32_t channels)
        : _width(width), _height(height), _imageData(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();

        switch (channels)
        {
        case 1:
            _internalFormat = GL_ALPHA8;
            _dataFormat = GL_ALPHA;
            break;

        case 3:
            _internalFormat = GL_RGB8;
            _dataFormat = GL_RGB;
            break;

        case 4:
            _internalFormat = GL_RGBA8;
            _dataFormat = GL_RGBA;
            break;
        default:
            TEMPEST_ERROR("Channel type not supported. Please select a textures with RGBA = 4, RGB = 3, or ALPHA = 1 channel.");
            _internalFormat = 0;
            _dataFormat = 0;
            break;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        //This might be a problem for text rendering.
        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : _width(width), _height(height), _imageData(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();
        _internalFormat = GL_RGBA8;
        _dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        _path(path), _imageData(nullptr)
    {
        TEMPEST_PROFILE_FUNCTION();
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        {
            TEMPEST_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) - stbi_load");
            _imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        TEMPEST_CORE_ASSERT(_imageData != nullptr, "Image could not be found or loaded!");

        _width = width;
        _height = height;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        _internalFormat = internalFormat;
        _dataFormat = dataFormat;

        glCreateTextures(GL_TEXTURE_2D, 1, &_textureID);
        glTextureStorage2D(_textureID, 1, _internalFormat, _width, _height);

        glTextureParameteri(_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_textureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(_textureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, _imageData);

        getDataSection(16, 15, 4, 2);

        stbi_image_free(_imageData);
    }

    OpenGLTexture2D::~OpenGLTexture2D() 
    {
        TEMPEST_PROFILE_FUNCTION();
        if (_imageData != nullptr)
        {
            stbi_image_free(_imageData);
        }
        glDeleteTextures(1, &_textureID);
    }

    uint32_t OpenGLTexture2D::getRendererID() const
    {
        return _textureID;
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size) 
    {
        switch (_dataFormat)
        {
        case GL_ALPHA:
            TEMPEST_CORE_ASSERT(size == _width * _height, "The buffer has to be the entire size of the texture.");
            break;

        case GL_RGB:
        {
            uint32_t bpp = 3;
            TEMPEST_CORE_ASSERT(size == _width * _height * bpp, "The buffer has to be the entire size of the texture.");
        }
            break;

        case GL_RGBA:
        {
            uint32_t bpp = 4;
            TEMPEST_CORE_ASSERT(size == _width * _height * bpp, "The buffer has to be the entire size of the texture.");
        }
            break;
        }

        glTextureSubImage2D(_textureID, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::saveData(const std::string& path) 
    {
        TEMPEST_CORE_ASSERT(_imageData == nullptr, "You cannot overwrite texture data that already exists.");

        TEMPEST_PROFILE_FUNCTION();
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        {
            TEMPEST_PROFILE_SCOPE("OpenGLTexture2D::OpenGLTexture2D(const std::string&) - stbi_load");
            _imageData = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        _width = width;
        _height = height;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        _internalFormat = internalFormat;
        _dataFormat = dataFormat;
    }

    stbi_uc* OpenGLTexture2D::getData() const 
    {
        TEMPEST_PROFILE_FUNCTION();
        TEMPEST_CORE_ASSERT(_imageData != nullptr, "There is no data to return!");
        return _imageData;
    }

    bool OpenGLTexture2D::isTransparent(int width, int height) const
    {
        TEMPEST_PROFILE_FUNCTION();
        TEMPEST_CORE_ASSERT(_imageData != nullptr, "Image data has been deleted!");
        TEMPEST_CORE_ASSERT(_internalFormat == GL_RGBA8, "The channels are not RGBA 8-bit");

        int stride = 4;

        //Checks over the image data, looks for each alpha pixel found at the offset of 4, in the 1D buffer.
        //Then checks over the next 4 index along for the next alpha pixel. If they are all 0 then it's transparent.
        for (int pixelIndex = 3; pixelIndex < width * height * stride; pixelIndex += 4)
        {
            if (_imageData[pixelIndex] != 0)
            {
                return false;
            }
        }

        return true;
    }

    //The reason this function is so denise it that we are looking for transparent pixels that are in _imageData
    //_imageData is a 1D array of unsigned char's. So we need to transpose 2D coordinates to a 1D coordinate system 
    //Not only that because OpenGL needs the y-axis flip we have to search the y-axis upside down.
    //We aren't just looking to see if all RGBA pixels are 0, we just need to find the A pixels and check they are 0
    //So that means, starting from index 0, we need to move along 4 index values to get to the next A pixels.
    //So 3, 7, 11 are all alpha pixels in the _imageData array. 
    bool OpenGLTexture2D::isTransparent(int x, int y, int width, int height) const
    {
        TEMPEST_PROFILE_FUNCTION();
        TEMPEST_CORE_ASSERT(_imageData != nullptr, "Image data has been deleted!");
        TEMPEST_CORE_ASSERT(_internalFormat == GL_RGBA8, "The channels are not RGBA 8-bit");

        //I don't know why we add one here, it just makes it work.
        int xStartingPixel = x + 1;
        int yStartingPixel = y + 1;
        int stride = 4;

        //X-Axis
        //(stride * xStartingPixel) - 1 is the starting position of the xPos. We take the starting position * by the stride
        //but because we are counting from 0 we need to - 1 to get to the correct offset.
        //((stride * xStartingPixel) - 1) + width is the starting positiong + the width of the section of the image.
        //We then move along 4 to match the stride.

        //Y-Axis - Remember we don't stride by 4 here because this is just moving through images columns of pixels. 
        //_height - yStartingPixel is the starting position because the image is inverted in the y-axis.
        //(_height - (yStartingPixel + hieght)) give up the top of the image region by adding the height to the starting position.
        //We just decrement and by 1 because yPos starts with a larger value, than our condition (_height - (yStartingPixel + height))

        //Index position
        //(yPos * (_width * stride)) + xPos So (yPos * _width) + xPos is the correct way to transpose 2D coordinate to a 1D point on a line.
        //However each point on the like is either R, G, B or A making 1 pixel value so the width is actually 4 times it's pixel width.
        for (int xPos = (stride * xStartingPixel) - 1; xPos < ((stride * xStartingPixel) - 1) + width; xPos += stride)
        {
            for (int yPos = _height - yStartingPixel; yPos > (_height - (yStartingPixel + height)); yPos--)
            {
                if (_imageData[(yPos * (_width * stride)) + xPos] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool OpenGLTexture2D::isTransparent(int width, int height, stbi_uc* imageData) const
    {
        TEMPEST_PROFILE_FUNCTION();
        TEMPEST_CORE_ASSERT(imageData != nullptr, "Image data has been deleted!");
        TEMPEST_CORE_ASSERT(_internalFormat == GL_RGBA8, "The channels are not RGBA 8-bit");

        int stride = 4;

        //Checks over the image data, looks for each alpha pixel found at the offset of 4, in the 1D buffer.
        //Then checks over the next 4 index along for the next alpha pixel. If they are all 0 then it's transparent.
        for (int pixelIndex = 3; pixelIndex < width * height * stride; pixelIndex += 4)
        {
            if (imageData[pixelIndex] != 0)
            {
                return false;
            }
        }

        return true;
    }

    bool OpenGLTexture2D::isTransparent(int x, int y, int width, int height, stbi_uc *imageData) const
    {
        TEMPEST_PROFILE_FUNCTION();
        TEMPEST_CORE_ASSERT(imageData != nullptr, "Image data has been deleted!");
        TEMPEST_CORE_ASSERT(_internalFormat == GL_RGBA8, "The channels are not RGBA 8-bit");

        //I don't know why we add one here, it just makes it work.
        int xStartingPixel = x + 1;
        int yStartingPixel = y + 1;
        int stride = 4;

        //X-Axis
        //(stride * xStartingPixel) - 1 is the starting position of the xPos. We take the starting position * by the stride
        //but because we are counting from 0 we need to - 1 to get to the correct offset.
        //((stride * xStartingPixel) - 1) + width is the starting positiong + the width of the section of the image.
        //We then move along 4 to match the stride.

        //Y-Axis - Remember we don't stride by 4 here because this is just moving through images columns of pixels. 
        //_height - yStartingPixel is the starting position because the image is inverted in the y-axis.
        //(_height - (yStartingPixel + hieght)) give up the top of the image region by adding the height to the starting position.
        //We just decrement and by 1 because yPos starts with a larger value, than our condition (_height - (yStartingPixel + height))

        //Index position
        //(yPos * (_width * stride)) + xPos So (yPos * _width) + xPos is the correct way to transpose 2D coordinate to a 1D point on a line.
        //However each point on the like is either R, G, B or A making 1 pixel value so the width is actually 4 times it's pixel width.
        for (int xPos = (stride * xStartingPixel) - 1; xPos < ((stride * xStartingPixel) - 1) + width; xPos += stride)
        {
            for (int yPos = height - yStartingPixel; yPos > (height - (yStartingPixel + height)); yPos--)
            {
                if (imageData[(yPos * (width * stride)) + xPos] != 0)
                {
                    return false;
                }
            }
        }

        return true;
    }

    stbi_uc* OpenGLTexture2D::getDataSection(int x, int y, int width, int height)
    {
        int stride = 4;
        int lenghtOfArry = width * height * stride;

        stbi_uc *subImage = new stbi_uc[lenghtOfArry];

        int yPixelPosition = 0;
        int xStartPosition = (x * stride);
        int pixelWidth = (width * stride);
        int index = 0;

        for (int column = 0; column < height; column++)
        {
            yPixelPosition = (_height - 1) - (y + column);
            index = (yPixelPosition * (_width * stride)) + xStartPosition;
            memcpy(subImage + (pixelWidth * column), _imageData + index, pixelWidth);
        }

        bool test = true;

        for (int i = 0; i < lenghtOfArry; i++)
        {
            if (subImage[i] != 0)
            {
                test = false;
            }
        }

        return nullptr;
        //return subImage;
    }

    void OpenGLTexture2D::bind(uint32_t slot) const 
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindTextureUnit(slot, _textureID);
    }

    void OpenGLTexture2D::unbind(uint32_t slot) const
    {
        TEMPEST_PROFILE_FUNCTION();
        glBindTextureUnit(slot, 0);
    }
}