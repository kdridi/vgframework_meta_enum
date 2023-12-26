#pragma once

#include "gfx/Raytracing/BLAS.h"

namespace vg::gfx
{
    class CommandList;
}

namespace vg::gfx::vulkan
{
    class BLAS : public base::BLAS
    {
        using super = base::BLAS;

    public:
        BLAS(BLASUpdateType _blasUpdateType);
        ~BLAS();

        void addIndexedGeometry(const gfx::Buffer * _ib, core::uint _ibOffset, core::uint _indexCount, const gfx::Buffer * _vb, core::uint _vbOffset, core::uint _vertexCount, core::uint _vbStride);
        void clear();
        void init(bool _update = false);
        void update(gfx::CommandList * _cmdList);
        void build(gfx::CommandList * _cmdList, bool _update = false);

    private:
        core::vector<VkAccelerationStructureGeometryKHR>        m_VKRTGeometries = {};
        core::vector<uint32_t>                                  m_VKRTMaxPrimitives = {};
        core::vector<VkAccelerationStructureBuildRangeInfoKHR>  m_VKRTBuildRangeInfos = {};

        VkAccelerationStructureBuildGeometryInfoKHR             m_VKRTAccelStructInputs = {};
        VkAccelerationStructureKHR                              m_VKBLAS = VK_NULL_HANDLE;
    };
}