#version 450 core

#extension GL_EXT_shader_16bit_storage : require

layout(binding = 0) buffer B
{
    int in_i;
    uint in_u;
    float in_f;
    ivec2 in_ivec2;
    ivec3 in_ivec3;
    ivec4 in_ivec4;
    uvec3 in_uvec3;
    vec2 in_vec2;

    float16_t in_f16;
    int16_t in_i16;
    uint16_t in_u16;

    float16_t f16_out[12];
    f16vec2 f16v2_out[5];
    f16vec3 f16v3_out[2];
    f16vec4 f16v4_out[2];

    int16_t i16_out[10];
    i16vec2 i16v2_out[4];
    i16vec3 i16v3_out[2];
    i16vec4 i16v4_out[1];

    uint16_t u16_out[9];
    u16vec2 u16v2_out[4];
    u16vec3 u16v3_out[2];
    u16vec4 u16v4_out[1];
};

void main()
{
    // float16_t scalar constants & runtime
    f16_out[0] = float16_t(1);
    f16_out[1] = float16_t(1u);
    f16_out[2] = float16_t(0);
    f16_out[3] = float16_t(0.0);
    f16_out[4] = float16_t(true);
    f16_out[5] = float16_t(false);
    f16_out[6] = float16_t(in_i);
    f16_out[7] = float16_t(in_u);
    f16_out[8] = float16_t(in_f);
    f16_out[9] = float16_t(in_i != 0);
    f16_out[10] = float16_t(in_ivec2);
    f16_out[11] = float16_t(in_f16);

    // f16vec* constants & runtime
    f16v2_out[0] = f16vec2(ivec2(1, -2));
    f16v2_out[1] = f16vec2(1);
    f16v2_out[2] = f16vec2(in_ivec2);
    f16v2_out[3] = f16vec2(in_i);
    f16v2_out[4] = f16vec2(in_ivec4);
    f16v3_out[0] = f16vec3(uvec3(0u, 1u, 2u));
    f16v3_out[1] = f16vec3(in_uvec3);
    f16v4_out[0] = f16vec4(bvec4(true, false, true, false));
    f16v4_out[1] = f16vec4(in_ivec4);

    // int16_t scalar constants & runtime
    i16_out[0] = int16_t(3.3);
    i16_out[1] = int16_t(-3.7);
    i16_out[2] = int16_t(42u);
    i16_out[3] = int16_t(true);
    i16_out[4] = int16_t(-5);
    i16_out[5] = int16_t(in_f);
    i16_out[6] = int16_t(in_u);
    i16_out[7] = int16_t(in_i != 0);
    i16_out[8] = int16_t(in_vec2);
    i16_out[9] = int16_t(in_i16);

    // i16vec* constants & runtime
    i16v2_out[0] = i16vec2(vec2(1.5, -2.5));
    i16v2_out[1] = i16vec2(3.3);
    i16v2_out[2] = i16vec2(in_vec2);
    i16v2_out[3] = i16vec2(in_f);
    i16v3_out[0] = i16vec3(uvec3(1u, 2u, 3u));
    i16v3_out[1] = i16vec3(in_uvec3);
    i16v4_out[0] = i16vec4(bvec4(true, false, true, false));

    // uint16_t scalar constants & runtime
    u16_out[0] = uint16_t(3.3);
    u16_out[1] = uint16_t(42);
    u16_out[2] = uint16_t(true);
    u16_out[3] = uint16_t(5u);
    u16_out[4] = uint16_t(in_f);
    u16_out[5] = uint16_t(in_i);
    u16_out[6] = uint16_t(in_i != 0);
    u16_out[7] = uint16_t(in_vec2);
    u16_out[8] = uint16_t(in_u16);

    // u16vec* constants & runtime
    u16v2_out[0] = u16vec2(vec2(1.5, 2.5));
    u16v2_out[1] = u16vec2(3.3);
    u16v2_out[2] = u16vec2(in_vec2);
    u16v2_out[3] = u16vec2(in_f);
    u16v3_out[0] = u16vec3(ivec3(1, 2, 3));
    u16v3_out[1] = u16vec3(in_ivec3);
    u16v4_out[0] = u16vec4(bvec4(true, false, true, false));
}
