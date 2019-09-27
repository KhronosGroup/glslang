SamplerState       g_sSamp : register(s0);

[[spv::format_rgba32f]]    RWTexture1D <float4> g_tTex1df4 : register(t0);
[[spv::format_rg32f]]      RWTexture1D <int4>   g_tTex1di4;
[[spv::format_rgba8snorm]] RWTexture1D <uint4>  g_tTex1du4;

[[spv::format_rgba8i]]       RWTexture2D <float4> g_tTex2df4;
[[spv::format_r11fg11fb10f]] RWTexture2D <int4>   g_tTex2di4;
[[spv::format_r8snorm]]      RWTexture2D <uint4>  g_tTex2du4;

[[spv::format_rg8]]     RWTexture3D <float4> g_tTex3df4;
[[spv::format_rgba16i]] RWTexture3D <int4>   g_tTex3di4;
[[spv::format_r8i]]     RWTexture3D <uint4>  g_tTex3du4;

[[spv::format_rgba8ui]] RWTexture1DArray <float4> g_tTex1df4a;
[[spv::format_rg32ui]]  RWTexture1DArray <int4>   g_tTex1di4a;
[[spv::format_r16ui]]   RWTexture1DArray <uint4>  g_tTex1du4a;

[[spv::format_rgb10a2ui]] RWTexture2DArray <float4> g_tTex2df4a;
[[spv::format_r8ui]]      RWTexture2DArray <int4>   g_tTex2di4a;
[[spv::format_rgba16f]]   RWTexture2DArray <uint4>  g_tTex2du4a;

struct PS_OUTPUT
{
    float4 Color : SV_Target0;
    float  Depth : SV_Depth;
};

PS_OUTPUT main()
{
   PS_OUTPUT psout;

   psout.Color = 1.0;
   psout.Depth = 1.0;

   return psout;
}
