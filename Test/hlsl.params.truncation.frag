float scalarFunction(float f) {
  return f;
}

float4 main(float2 tc : TEXCOORD0) : SV_Target {
  return float4(scalarFunction(0.5 + tc));
}