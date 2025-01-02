#include "gfx/Raytracing/BLAS.h"

namespace vg::renderer
{
    //--------------------------------------------------------------------------------------
    VG_INLINE const Skeleton * MeshInstance::getInstanceSkeleton() const
    {
        return m_instanceSkeleton;
    }

    //--------------------------------------------------------------------------------------
    VG_INLINE const gfx::Buffer * MeshInstance::getSkinnedMeshBuffer() const
    {
        return m_skinnedMeshBuffer;
    }

    //--------------------------------------------------------------------------------------
    VG_INLINE const core::uint MeshInstance::getSkinnedMeshBufferOffset() const
    {
        return m_skinnedMeshBufferOffset;
    }

    //--------------------------------------------------------------------------------------
    VG_INLINE void MeshInstance::setInstanceBLAS(gfx::BLAS * _BLAS)
    {
        if (_BLAS != m_instanceBLAS)
        {
            VG_SAFE_RELEASE_ASYNC(m_instanceBLAS);
            m_instanceBLAS = _BLAS;
            VG_SAFE_INCREASE_REFCOUNT(m_instanceBLAS);
        }
    }

    //--------------------------------------------------------------------------------------
    VG_INLINE gfx::BLAS * MeshInstance::getInstanceBLAS() const
    {
        return m_instanceBLAS;
    }

    //--------------------------------------------------------------------------------------
    VG_INLINE bool MeshInstance::isSkinned() const
    {
        return nullptr != getInstanceSkeleton();
    }
}