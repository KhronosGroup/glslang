#version 440 core

struct VertexInfo {
    float position[3];
    float normal[3];
};

struct TriangleInfo {
    VertexInfo v[3];
};

buffer VertexCollection {
    TriangleInfo t[5];
};

void main()
{
    float f;
    f += t[0].v[0].position[0];
    f += t[gl_InstanceID].v[gl_InstanceID].position[gl_InstanceID];
    f += t[gl_InstanceID].v[gl_InstanceID].normal[gl_InstanceID];
    TriangleInfo tlocal[5] = t;
}
