#version 460 core

float foo(in float f, out int i, inout vec3 v)
{
    v.x = f;
    i = int(v.y);
    return v.z;
}
