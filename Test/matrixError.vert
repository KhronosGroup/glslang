#version 120

attribute vec3 v3;

uniform mat3x2 m32;

const mat2x4 m24 = mat2x4(1.0, 2.0, 
                          3.0, 4.0,
                          3.0, 4.0,
                          3.0, 4.0, 5.0);

void main()
{
    mat2x3 m23;
    vec3 a, b;

    a = v3 * m23;
    b = m32 * v3;
    m23.xy;

    gl_Position = vec4(m23 * m32 * v3, m24[2][4]);
}
