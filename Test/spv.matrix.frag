#version 130

uniform mat3 colorTransform;
in vec3 Color;
uniform mat4 m, n;

uniform mat4x3 um43;
uniform mat3x4 un34;

in vec4 v;

in vec3 u;

void main()
{
    gl_FragColor = vec4(un34[1]);
    gl_FragColor += vec4(Color * colorTransform, 1.0);

    if (m != n)
        gl_FragColor += v;
    else {
        gl_FragColor += m * v;
        gl_FragColor += v * (m - n);
    }

    mat3x4 m34 = outerProduct(v, u);
    m34 += mat3x4(v.x);
    m34 += mat3x4(u, u.x, u, u.x, u, u.x);

    if (m34 == un34)
        gl_FragColor += m34 * u;
    else
        gl_FragColor += (un34 * um43) * v;
}
