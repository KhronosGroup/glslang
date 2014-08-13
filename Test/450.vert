#version 450 core

out gl_PerVertex {
    float gl_CullDistance[3];
};

void main()
{
    gl_CullDistance[2] = 4.5;
}
