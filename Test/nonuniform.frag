#version 450

nonuniformEXT in vec4 nu_inv4;
nonuniformEXT float nu_gf;

nonuniformEXT out vec4 nu_outv4;           // ERROR, out
nonuniformEXT uniform vec4 nu_uv4;         // ERROR, uniform
nonuniformEXT const float nu_constf = 1.0; // ERROR, const

void foo(nonuniformEXT int nupi)
{
}

void main()
{
    nonuniformEXT int nu_li;
    nonuniformEXT const int nu_ci = 2; // ERROR, const

    foo(nu_li);

    int a;
    nu_li = nonuniformEXT(a) + nonuniformEXT(a * 2);
    nu_li = nonuniformEXT(a, a);       // ERROR, too many arguments
    nu_li = nonuniformEXT();           // ERROR, no arguments
}