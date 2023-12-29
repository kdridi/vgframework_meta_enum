#pragma once

#define DEFERRED_LIGHTING_THREADGROUP_SIZE_X 16
#define DEFERRED_LIGHTING_THREADGROUP_SIZE_Y 16

#include "system/constants.hlsli"
#include "system/packing.hlsli"

struct DeferredLightingConstants
{
    void setScreenSize      (uint2 _size)   { width_height = packUint16(_size.xy);}
    uint2 getScreenSize     ()              { return unpackUint16(width_height); }

    void setAlbedoGBuffer   (uint _albedo)  { albedo_normal = packUint16low(albedo_normal, _albedo); }
    uint getAlbedoGBuffer   ()              { return unpackUint16low(albedo_normal); }

    void setNormalGBuffer   (uint _normal)  { albedo_normal = packUint16high(albedo_normal, _normal); }
    uint getNormalGBuffer   ()              { return unpackUint16high(albedo_normal); }

    void setPBRGBuffer      (uint _pbr)     { pbr_unused = packUint16high(pbr_unused, _pbr); }
    uint getPBRGBuffer      ()              { return unpackUint16high(pbr_unused); }

    void setDepth           (uint _depth)   { depth_stencil = packUint16low(depth_stencil, _depth); }
    uint getDepth           ()              { return unpackUint16low(depth_stencil); }

    void setStencil         (uint _stencil) { depth_stencil = packUint16high(depth_stencil, _stencil); }
    uint getStencil         ()              { return unpackUint16high(depth_stencil); }

    void setRWBufferOut     (uint _rwbuffer){ rwbuffer = packUint16low(rwbuffer, _rwbuffer); }
    uint getRWBufferOut     ()              { return unpackUint16low(rwbuffer); }

    uint width_height;
    uint albedo_normal;
    uint pbr_unused;
    uint depth_stencil;
    uint rwbuffer;
};

#define DeferredLightingConstantsCount sizeof(DeferredLightingConstants)/sizeof(u32)

#ifndef __cplusplus
DECL_ROOTCONSTANTS(DeferredLightingConstants, deferredLightingConstants, 0, 0);
#endif