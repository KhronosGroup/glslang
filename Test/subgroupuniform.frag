#version 450

int subgroupuniformEXT;

#extension GL_EXT_subgroupuniform_qualifier : enable
#extension GL_EXT_nonuniform_qualifier : enable

subgroupuniformEXT in vec4 su_inv4;
subgroupuniformEXT float su_gf;

subgroupuniformEXT out vec4 su_outv4;           // ERROR, out
subgroupuniformEXT uniform vec4 su_uv4;         // ERROR, uniform
subgroupuniformEXT const float su_constf = 1.0; // ERROR, const

subgroupuniformEXT int foo(subgroupuniformEXT int nupi, subgroupuniformEXT out int f)
{
    return nupi;
}

void main()
{
    subgroupuniformEXT int su_li;
    subgroupuniformEXT const int su_ci = 2; // ERROR, const

    foo(su_li, su_li);

    int a;
    su_li = subgroupuniformEXT(a) + subgroupuniformEXT(a * 2);
    su_li = subgroupuniformEXT(a, a);       // ERROR, too many arguments
    su_li = subgroupuniformEXT();           // ERROR, no arguments

    nonuniformEXT
    subgroupuniformEXT int nu_su_li1; // ERROR, mismatched qualifiers
    subgroupuniformEXT
    nonuniformEXT int nu_su_li2; // ERROR, mismatched qualifiers
}

layout(location=1) in struct S { float a; subgroupuniformEXT float b; } ins;  // ERROR, not on member
layout(location=3) in inbName { float a; subgroupuniformEXT float b; } inb;   // ERROR, not on member
