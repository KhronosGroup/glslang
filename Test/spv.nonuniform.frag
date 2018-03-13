#version 450

layout(location=0) nonuniformEXT in vec4 nu_inv4;
nonuniformEXT float nu_gf;

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
}