#version 120

uniform vec4 u[3];

varying vec2 v[2];

void main()
{
    int a[5];

    vec2 t = v[0] + v[1];

    gl_FragColor = vec4(u.length() * v.length() * a.length());
}
