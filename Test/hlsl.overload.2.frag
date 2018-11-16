float randPos(float3 p)
{
  return frac(sin(dot(p.xyz, float3(1, -2.7813, 3.01))*12.9898) * 43758.5453);
}
float rand(float p)
{
  return frac(sin(p*12.9898) * 43758.5453);
}

float3 v2 : register(c0);
float2 v1 : register(c1);

float4 main() : SV_Target {
  float randVal = rand(randPos(v2)+sin(v1*0.1317));
  return 0;
}