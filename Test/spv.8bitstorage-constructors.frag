#version 450 core

#extension GL_EXT_shader_8bit_storage : require

layout(binding = 0) buffer B
{
    int in_i;
    uint in_u;
    float in_f;
    ivec3 in_ivec3;
    uvec3 in_uvec3;
    vec2 in_vec2;

    int8_t in_i8;
    uint8_t in_u8;

    int8_t i8_out[10];
    i8vec2 i8v2_out[4];
    i8vec3 i8v3_out[2];
    i8vec4 i8v4_out[1];

    uint8_t u8_out[9];
    u8vec2 u8v2_out[4];
    u8vec3 u8v3_out[2];
    u8vec4 u8v4_out[1];
};

void main()
{
    // int8_t scalar constants & runtime
    i8_out[0] = int8_t(3.3);
    i8_out[1] = int8_t(-3.7);
    i8_out[2] = int8_t(42u);
    i8_out[3] = int8_t(true);
    i8_out[4] = int8_t(-5);
    i8_out[5] = int8_t(in_f);
    i8_out[6] = int8_t(in_u);
    i8_out[7] = int8_t(in_i != 0);
    i8_out[8] = int8_t(in_vec2);
    i8_out[9] = int8_t(in_i8);

    // i8vec* constants & runtime
    i8v2_out[0] = i8vec2(vec2(1.5, -2.5));
    i8v2_out[1] = i8vec2(3.3);
    i8v2_out[2] = i8vec2(in_vec2);
    i8v2_out[3] = i8vec2(in_f);
    i8v3_out[0] = i8vec3(uvec3(1u, 2u, 3u));
    i8v3_out[1] = i8vec3(in_uvec3);
    i8v4_out[0] = i8vec4(bvec4(true, false, true, false));

    // uint8_t scalar constants & runtime
    u8_out[0] = uint8_t(3.3);
    u8_out[1] = uint8_t(42);
    u8_out[2] = uint8_t(true);
    u8_out[3] = uint8_t(5u);
    u8_out[4] = uint8_t(in_f);
    u8_out[5] = uint8_t(in_i);
    u8_out[6] = uint8_t(in_i != 0);
    u8_out[7] = uint8_t(in_vec2);
    u8_out[8] = uint8_t(in_u8);

    // u8vec* constants & runtime
    u8v2_out[0] = u8vec2(vec2(1.5, 2.5));
    u8v2_out[1] = u8vec2(3.3);
    u8v2_out[2] = u8vec2(in_vec2);
    u8v2_out[3] = u8vec2(in_f);
    u8v3_out[0] = u8vec3(ivec3(1, 2, 3));
    u8v3_out[1] = u8vec3(in_ivec3);
    u8v4_out[0] = u8vec4(bvec4(true, false, true, false));
}
