#version 450

#extension GL_EXT_nonuniform_qualifier : enable

layout(location=0) nonuniformEXT in vec4 nu_inv4;
nonuniformEXT float nu_gf;
layout(location=1) in nonuniformEXT flat int nu_ii;
layout(binding=0) uniform sampler2D s2d[];

nonuniformEXT int foo(nonuniformEXT int nupi, nonuniformEXT out int f)
{
    return nupi;
}

void main()
{
    nonuniformEXT int nu_li;

    int a = foo(nu_li, nu_li);
    nu_li = nonuniformEXT(a) + nonuniformEXT(a * 2);

    float b;
    b = nu_inv4.x * nu_gf;
    texture(s2d[nu_ii], vec2(0.5));
}