#include "OpenGLFramebuffer.h"

#include <GL/glew.h>

namespace Tempest 
{
    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec) : _framebufferSpec(spec)
    {
        invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() 
    {
        glDeleteFramebuffers(1, &_rendererID);
    }

    void OpenGLFramebuffer::bind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);
    }

    void OpenGLFramebuffer::unbind() 
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    const FramebufferSpec OpenGLFramebuffer::getFramebuffer() const
    {
        return _framebufferSpec;
    }

    uint32_t OpenGLFramebuffer::getColourAttachmentRendererID() const
    {
        return _colourAttachment;
    }

    void OpenGLFramebuffer::invalidate()
    {
        glCreateFramebuffers(1, &_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, _rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &_colourAttachment);
        glBindTexture(GL_TEXTURE_2D, _colourAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _framebufferSpec.width, _framebufferSpec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colourAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, _depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _framebufferSpec.width, _framebufferSpec.height);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, _framebufferSpec.width, _framebufferSpec.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depthAttachment, 0);

        TEMPEST_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}