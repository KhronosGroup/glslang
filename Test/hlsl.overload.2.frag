float4 texelFetch(Texture2D<float4> a, int2 tc, int lod) { return a.Load(int3(tc, lod)); }
float3 texelFetch(Texture2D<float3> a, int2 tc, int lod) { return a.Load(int3(tc, lod)); }
float2 texelFetch(Texture2D<float2> a, int2 tc, int lod) { return a.Load(int3(tc, lod)); }
float texelFetch(Texture2D<float> a, int2 tc, int lod) { return a.Load(int3(tc, lod)); }
float4 texelFetch(Texture2DArray<float4> a, int3 tc, int lod) { return a.Load(int4(tc, lod)); }
float3 texelFetch(Texture2DArray<float3> a, int3 tc, int lod) { return a.Load(int4(tc, lod)); }
float2 texelFetch(Texture2DArray<float2> a, int3 tc, int lod) { return a.Load(int4(tc, lod)); }
float texelFetch(Texture2DArray<float> a, int3 tc, int lod) { return a.Load(int4(tc, lod)); }

float4 texelFetch(Buffer<float4> a, int tc) { return a[tc]; }
float3 texelFetch(Buffer<float3> a, int tc) { return a[tc]; }
float2 texelFetch(Buffer<float2> a, int tc) { return a[tc]; }
float texelFetch(Buffer<float> a, int tc) { return a[tc]; }

float randPos(float3 p)
{
  return frac(sin(dot(p.xyz, float3(1, -2.7813, 3.01))*12.9898) * 43758.5453);
}
float rand(float p)
{
  return frac(sin(p*12.9898) * 43758.5453);
}

Buffer<float4> fetchBuffer : register(t0);

float3 v2 : register(c0);
float2 v1 : register(c1);

float4 main() : SV_Target {
  int i = 0;
  float randVal = rand(randPos(v2)+sin(v1*0.1317));
  return clamp(randVal, i, i + 1);
  return 0;
  //return texelFetch(fetchBuffer, uint(1));
}