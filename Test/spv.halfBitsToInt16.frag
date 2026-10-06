#version 450

#extension GL_EXT_shader_explicit_arithmetic_types : require

layout(location = 0) in vec4 v;
layout(location = 0) out ivec4 o;
layout(location = 1) out uvec4 u;

void main()
{
    o.x = halfBitsToInt16(float16_t(v.x));
    o.xy += halfBitsToInt16(f16vec2(v.xy));
    o.xyz += halfBitsToInt16(f16vec3(v.xyz));
    o += halfBitsToInt16(f16vec4(v));

    u.x = halfBitsToUint16(float16_t(v.x));
    u.xy += halfBitsToUint16(f16vec2(v.xy));
    u.xyz += halfBitsToUint16(f16vec3(v.xyz));
    u += halfBitsToUint16(f16vec4(v));
}
