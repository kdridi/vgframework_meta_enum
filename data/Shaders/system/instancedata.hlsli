#pragma once

#include "system/packing.hlsli"
#include "system/table.hlsli"
#include "system/materialdata.hlsli"
#include "system/vertex.hlsli"

#define GPU_INSTANCE_DATA_ALIGNMENT 16

//--------------------------------------------------------------------------------------
// 1xGPUInstanceData, N*GPUBatchData : In instance stream, 1 'GPUInstanceData' is followed by N 'GPUBatchData' for every batch (<=>material)
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// GPUInstanceData
// Materials use 16-bits indices and up to 16 materials per instance are supported
//--------------------------------------------------------------------------------------
struct GPUBatchData
{
    uint m_material;
    uint m_startIndex;

    void setMaterialIndex               (uint _handle)                                      { m_material = _handle; }
    uint getMaterialBytesOffset         ()                                                  { return m_material * sizeof(GPUMaterialData); }

    void setStartIndex                  (uint _startIndex)                                  { m_startIndex = _startIndex; }
    uint getStartIndex                  ()                                                  { return m_startIndex; }

    #ifndef __cplusplus
    GPUMaterialData loadGPUMaterialData  ()                                                 { return getBuffer(RESERVEDSLOT_BUFSRV_MATERIALDATA).Load<GPUMaterialData>(getMaterialBytesOffset()); }
    #endif
};

//--------------------------------------------------------------------------------------
// GPUInstanceData
// Materials use 16-bits indices and up to 16 materials per instance are supported
//--------------------------------------------------------------------------------------
struct GPUInstanceData
{
    // m_header[0]: MaterialCount | VertexFormat<<8 | unused<<16 | unused<<24   (8 bits x 4)
    // m_header[1]: InstanceColor                                               (32 bits)
    // m_header[2]: (IndexSize + IB) | VB                                       (16 bits x 2)
    // m_header[3]: VBOffset                                                    (32 bits)
    uint m_header[4];   

    void setMaterialCount               (uint _count)                                       { m_header[0] = packR8(m_header[0], _count); }
    uint getMaterialCount               ()                                                  { return unpackR8(m_header[0]); }

    void setVertexFormat                (VertexFormat _vertexFormat)                        { m_header[0] = packG8(m_header[0], (uint)_vertexFormat); }
    VertexFormat getVertexFormat        ()                                                  { return (VertexFormat)unpackG8(m_header[0]); }

    void setInstanceColor               (float4 _color)                                     { m_header[1] = packRGBA8(_color); }
    float4 getInstanceColor             ()                                                  { return unpackRGBA8(m_header[1]); }

    void setIndexBuffer                 (uint _ib, uint _indexSize = 2, uint _offset = 0)   { m_header[2] = packUint16low(m_header[2], _indexSize == 4 ? (_ib | 0x8000) : _ib); }
    uint getIndexBufferHandle           ()                                                  { return unpackUint16low(m_header[2]) & ~0x8000; }
    uint getIndexSize                   ()                                                  { return (unpackUint16low(m_header[2]) & 0x8000) ? 4 : 2; }

    void setVertexBuffer                (uint _vb, uint _offset = 0)                        { m_header[2] = packUint16high(m_header[2], _vb); m_header[3] = _offset; }
    uint getVertexBufferHandle          ()                                                  { return unpackUint16high(m_header[2]); }
    uint getVertexBufferOffset          ()                                                  { return m_header[3]; }

    #ifndef __cplusplus

    GPUBatchData loadGPUBatchData        (uint _instanceDataOffset, uint _batchIndex)
    {
        GPUBatchData batchData = (GPUBatchData)0;

        uint batchDataOffset = 0;
        if (_batchIndex < getMaterialCount())
            batchData = getBuffer(RESERVEDSLOT_BUFSRV_INSTANCEDATA).Load<GPUBatchData>(_instanceDataOffset + sizeof(GPUInstanceData) + _batchIndex * sizeof(GPUBatchData));

        return batchData;
    }

    GPUMaterialData loadGPUMaterialData  (uint _instanceDataOffset, uint _matID)
    {
        GPUBatchData batchData = loadGPUBatchData(_instanceDataOffset, _matID);
        return batchData.loadGPUMaterialData();
    }
    #endif
};