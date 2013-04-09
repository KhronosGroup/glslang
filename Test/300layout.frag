#version 300 es

in vec4 pos;
in vec4 color;

layout(location = 7) out vec4 c;
layout(location = 3) out vec4 p;

//layout(std140) uniform Transform { // layout of this block is std140
//    mat4 M1; // row_major
//    layout(column_major) mat4 M2; // column major
//    mat3 N1; // row_major
//};
//
//uniform T2 { // layout of this block is shared
//...
//};
//
//layout(column_major) uniform T3 { // shared and column_major
//    mat4 M3; // column_major
//    layout(row_major) mat4 m4; // row major
//    mat3 N2; // column_major
//};

void main()
{
    c = color;
    p = pos;
}
