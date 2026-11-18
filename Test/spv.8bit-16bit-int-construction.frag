#version 450 core

#extension GL_EXT_shader_8bit_storage : enable
#extension GL_EXT_shader_16bit_storage : enable

buffer B
{
    int8_t in_i8;
    int16_t in_i16;
    uint8_t in_u8;
    uint16_t in_u16;
    i8vec2 in_i8v2;
    i16vec2 in_i16v2;
    u8vec2 in_u8v2;
    u16vec2 in_u16v2;

    int8_t i8_from_i16;
    int16_t i16_from_i8;
    uint8_t u8_from_u16;
    uint16_t u16_from_u8;

    int8_t i8_from_i16_rt;
    int16_t i16_from_i8_rt;
    uint8_t u8_from_u16_rt;
    uint16_t u16_from_u8_rt;

    i8vec2 i8v2_from_i16v2;
    i16vec2 i16v2_from_i8v2;
    u8vec2 u8v2_from_u16v2;
    u16vec2 u16v2_from_u8v2;
};

void main()
{
    i8_from_i16 = int8_t(int16_t(1));
    i16_from_i8 = int16_t(int8_t(1));
    u8_from_u16 = uint8_t(uint16_t(1));
    u16_from_u8 = uint16_t(uint8_t(1));

    i8_from_i16_rt = int8_t(in_i16);
    i16_from_i8_rt = int16_t(in_i8);
    u8_from_u16_rt = uint8_t(in_u16);
    u16_from_u8_rt = uint16_t(in_u8);

    i8v2_from_i16v2 = i8vec2(in_i16v2);
    i16v2_from_i8v2 = i16vec2(in_i8v2);
    u8v2_from_u16v2 = u8vec2(in_u16v2);
    u16v2_from_u8v2 = u16vec2(in_u8v2);
}
