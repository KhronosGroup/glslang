#version 150 core

in vec4 iv4;

uniform float ps;
uniform int ui;

invariant gl_Position;

struct s1 {
    int a;
    int a2;
    vec4 b[3];
};

struct s2 {
    int c;
    s1 d[4];
};

out s2 s2out;

void main()
{
    gl_Position = iv4;
    gl_PointSize = ps;
    gl_ClipDistance[2] = iv4.x;
    int i;
    s2out.d[i].b[2].w = ps;
    
    // test recovery from nonsupported built-ins    
    //float n1 = noise1(2.4);
    //n1 = noise1(vec4(n1));
    //vec2 n2 = noise2(vec3(n1));
    //vec3 n3 = noise3(n2);
    //vec4 n4 = noise4(n3);
}

out float gl_ClipDistance[4];
