#version 450

layout(location=0) nonuniformEXT in vec4 nu_inv4;
nonuniformEXT float nu_gf;

void foo(nonuniformEXT int nupi)
{
}

void main()
{
    nonuniformEXT int nu_li;

    foo(nu_li);

    int a;
    nu_li = nonuniformEXT(a) + nonuniformEXT(a * 2);

    float b;
    b = nu_inv4.x * nu_gf;
}