#pragma once

namespace vg::gfx
{
    class RenderPassContext;
}

namespace vg::renderer
{
    enum class ShaderPass : core::u8;

    class RenderContext
    {
    public:
        RenderContext() :
            m_view(core::float4x4::identity()),
            m_proj(core::float4x4::identity()),
            m_renderPass(nullptr),
            m_shaderPass((ShaderPass)0),
            m_toolmode(false),
            m_raytracing(false),
            m_wireframe(false),
            m_alphatest(false)
        {

        }

        core::float4x4                  m_view;
        core::float4x4                  m_proj;
        const gfx::RenderPassContext *  m_renderPass;
        ShaderPass                      m_shaderPass;
        bool                            m_toolmode     : 1;
        bool                            m_raytracing   : 1;
        bool                            m_wireframe    : 1;
        bool                            m_alphatest    : 1;
    };
}