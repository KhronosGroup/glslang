#version 460 core
#extension GL_EXT_shader_explicit_arithmetic_types : enable

void a(){
    int i0 = int(1e20);
    int i1 = int(-1e20);
    uint u0 = uint(1e20);
    uint u1 = uint(-1.0);
    int8_t b0 = int8_t(300.0);
    uint8_t b1 = uint8_t(-300.0);
    int16_t s0 = int16_t(1e10);
    int64_t l0 = int64_t(1e30lf);
    uint64_t l1 = uint64_t(1e30lf);
    int i2 = int(2147483647.0);
    int i3 = int(-2.5);
}
