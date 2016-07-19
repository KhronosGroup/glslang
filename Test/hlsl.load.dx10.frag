SamplerState       g_sSamp : register(s0);

uniform Texture1D <float4> g_tTex1df4 : register(t0);
Texture1D <int4>   g_tTex1di4;
Texture1D <uint4>  g_tTex1du4;

Texture2D <float4> g_tTex2df4;
Texture2D <int4>   g_tTex2di4;
Texture2D <uint4>  g_tTex2du4;

Texture3D <float4> g_tTex3df4;
Texture3D <int4>   g_tTex3di4;
Texture3D <uint4>  g_tTex3du4;

TextureCube <float4> g_tTexcdf4;
TextureCube <int4>   g_tTexcdi4;
TextureCube <uint4>  g_tTexcdu4;

Texture1DArray <float4> g_tTex1df4a;
Texture1DArray <int4>   g_tTex1di4a;
Texture1DArray <uint4>  g_tTex1du4a;

Texture2DArray <float4> g_tTex2df4a;
Texture2DArray <int4>   g_tTex2di4a;
Texture2DArray <uint4>  g_tTex2du4a;

TextureCubeArray <float4> g_tTexcdf4a;
TextureCubeArray <int4>   g_tTexcdi4a;
TextureCubeArray <uint4>  g_tTexcdu4a;

struct PS_OUTPUT
{
    float4 Color : SV_Target0;
    float  Depth : SV_Depth;
};

PS_OUTPUT main()
{
   PS_OUTPUT psout;

   // Load, no offset
   g_tTex1df4.Load(int2(1,2));
   g_tTex1di4.Load(int2(1,2));
   g_tTex1du4.Load(int2(1,2));

   g_tTex2df4.Load(int3(1,2,3));
   g_tTex2di4.Load(int3(1,2,3));
   g_tTex2du4.Load(int3(1,2,3));

   g_tTex3df4.Load(int4(1,2,3,4));
   g_tTex3di4.Load(int4(1,2,3,4));
   g_tTex3du4.Load(int4(1,2,3,4));

   g_tTex1df4a.Load(int3(1,2,3));
   g_tTex1di4a.Load(int3(1,2,3));
   g_tTex1du4a.Load(int3(1,2,3));

   g_tTex2df4a.Load(int4(1,2,3,4));
   g_tTex2di4a.Load(int4(1,2,3,4));
   g_tTex2du4a.Load(int4(1,2,3,4));

   // Load, offset
   g_tTex1df4.Load(int2(1,2), 3);
   g_tTex1di4.Load(int2(1,2), 3);
   g_tTex1du4.Load(int2(1,2), 3);

   g_tTex2df4.Load(int3(1,2,3), int2(4,5));
   g_tTex2di4.Load(int3(1,2,3), int2(4,5));
   g_tTex2du4.Load(int3(1,2,3), int2(4,5));

   g_tTex3df4.Load(int4(1,2,3,4), int3(5,6,7));
   g_tTex3di4.Load(int4(1,2,3,4), int3(5,6,7));
   g_tTex3du4.Load(int4(1,2,3,4), int3(5,6,7));

   g_tTex1df4a.Load(int3(1,2,3), 4);
   g_tTex1di4a.Load(int3(1,2,3), 4);
   g_tTex1du4a.Load(int3(1,2,3), 4);

   g_tTex2df4a.Load(int4(1,2,3,4), int2(4,5));
   g_tTex2di4a.Load(int4(1,2,3,4), int2(4,5));
   g_tTex2du4a.Load(int4(1,2,3,4), int2(4,5));

   // TODO:
   // Load, SampleIndex
   // Load, SampleIndex, Offset

   psout.Color = 1.0;
   psout.Depth = 1.0;

   return psout;
}
