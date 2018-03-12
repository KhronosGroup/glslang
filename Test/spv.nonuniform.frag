#version 450

layout(location=0) nonuniformEXT in vec4 nu_inv4;
nonuniformEXT float nu_gf;
layout(location=1) in struct S { float a; nonuniformEXT float b; } ins;
layout(location=3) in inbName { nonuniformEXT float a; float b; } inb;

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
    b = ins.a + inb.a;
}