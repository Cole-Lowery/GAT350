#include "RenderTexture.h"
#include "Engine.h"

namespace neu {
    RenderTexture::~RenderTexture() {
        if (m_fbo) glDeleteFramebuffers(1, &m_fbo);
        if (m_depthBuffer) glDeleteRenderbuffers(1, &m_depthBuffer);
    }

    // Allow creating a RenderTexture via Resources().Get<RenderTexture>(name)
    // by creating a default-sized render target based on the renderer/window.
    bool RenderTexture::Load(const std::string& filename) {
        // If you want to encode width/height in `filename`, parse it here.
        // For now create a RT at the current renderer size.
        int width = GetEngine().GetRenderer().GetWidth();
        int height = GetEngine().GetRenderer().GetHeight();
        if (width <= 0 || height <= 0) {
            LOG_WARNING("Renderer size is invalid when creating RenderTexture from '{}': {}x{}", filename, width, height);
            return false;
        }
        return Create(width, height, true);
    }

    bool RenderTexture::Create(int width, int height, bool depth) {
        m_size = glm::ivec2{ width, height };

        // framebuffer
        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

        // color texture
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Attach the texture to the framebuffer (correct API)
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

        // Make sure we set the draw buffers for the FBO
        GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, drawBuffers);

        // depth (optional)
        if (depth) {
            glGenRenderbuffers(1, &m_depthBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);

            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            LOG_WARNING("Error creating framebuffer");
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return true;
    }

    void RenderTexture::BindFramebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void RenderTexture::UnbindFramebuffer() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}