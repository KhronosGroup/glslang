#version 300 es

layout(location = 7) in vec4 c;
layout(LocatioN = 3) in vec4 p;
out vec4 pos;
out vec4 color;

layout(shared, column_major, row_major) uniform mat4 m4; // default is now shared and row_major

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
    pos = p * m4;
    color = c;
}
