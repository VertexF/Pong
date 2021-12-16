#ifndef OPENGL_FRAMEBUFFER_HDR
#define OPENGL_FRAMEBUFFER_HDR

#include "Tempest/Renderer/Framebuffer.h"

namespace Tempest 
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpec& spec);
        virtual ~OpenGLFramebuffer();

        virtual void bind() override;
        virtual void unbind() override;

        virtual const FramebufferSpec getFramebuffer() const override;
        virtual uint32_t getColourAttachmentRendererID() const override;

        void invalidate();
    private:
        uint32_t _rendererID;
        uint32_t _colourAttachment;
        uint32_t _depthAttachment;

        FramebufferSpec _framebufferSpec;
    };
}

#endif // !OPENGL_FRAMEBUFFER_HDR
