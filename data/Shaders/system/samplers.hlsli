#ifndef _SAMPLERS__HLSLI_
#define _SAMPLERS__HLSLI_
#ifndef __cplusplus

//--------------------------------------------------------------------------------------
// Should match enum in "SamplerState_consts.h"
//--------------------------------------------------------------------------------------

#ifdef _DX12

sampler nearestClamp      : register(s0, space0);
sampler nearestRepeat     : register(s1, space0);
sampler linearClamp       : register(s2, space0);
sampler linearRepeat      : register(s3, space0);
sampler anisotropicClamp  : register(s4, space0);
sampler anisotropicRepeat : register(s5, space0);

SamplerComparisonState shadowcmp     : register(s6, space0);

#elif defined(_VULKAN)

[[vk::binding(0, 1)]] sampler vkSamplerArray[7]  : register(s0, space1);
#define nearestClamp      vkSamplerArray[0]
#define nearestRepeat     vkSamplerArray[1]
#define linearClamp       vkSamplerArray[2]
#define linearRepeat      vkSamplerArray[3]
#define anisotropicClamp  vkSamplerArray[4]
#define anisotropicRepeat vkSamplerArray[5]

[[vk::binding(0, 1)]] SamplerComparisonState vkSamplerComparisonArray[7]  : register(s0, space1);
#define shadowcmp     vkSamplerComparisonArray[6]

#endif

#endif // __cplusplus
#endif // _SAMPLERS__HLSLI_