#version 440 core

layout(std140, row_major) uniform nameless {
    vec3 anonMember1;
    mat3x2 m23;
    int scalarAfterm23;
    vec4 anonDeadMember2;
    vec4 anonMember3;
    int scalarBeforeArray;
    float floatArray[5];
    int scalarAfterArray;
};

layout(std140, column_major) uniform c_nameless {
    vec3 c_anonMember1;
    mat3x2 c_m23;
    int c_scalarAfterm23;
    vec4 c_anonDeadMember2;
    vec4 c_anonMember3;
};

layout(std140) uniform named {
    vec3 deadMember1;
    int scalar;
    vec4 member2;
    vec4 member3;
    vec2 memvec2;
    float memf1;
    bool  memf2;
    int   memf3;
    vec2 memvec2a;
} ablock;

layout(std140) uniform namelessdead {
    int a;
};

layout(std140) uniform namedDead {
    int b;
} bblock;

struct TS {
    int a;
    int dead;
};

uniform TS s;

uniform float uf1;
uniform float uf2;
uniform float ufDead3;
uniform float ufDead4;

uniform uimage2D image_ui2D;
uniform sampler2D sampler_2D;
uniform sampler2DMSArray sampler_2DMSArray;

const bool control = true;

void deadFunction()
{
    vec3 v3 = ablock.deadMember1;
    vec4 v = anonDeadMember2;
    float f = ufDead4;
}

void liveFunction2()
{
    vec3 v = anonMember1;
    float f = uf1;
}

void liveFunction1(uimage2D p_ui2D, sampler2D p_2D, sampler2DMSArray p_2DMSArray)

{
    liveFunction2();
    float f = uf2;
    vec4 v = ablock.member3;
}

void main()
{
    liveFunction1(image_ui2D, sampler_2D, sampler_2DMSArray);
    liveFunction2();

    if (! control)
        deadFunction();

    float f;

    if (control) {
        liveFunction2();
        f = anonMember3.z;
        f = s.a;
        f = ablock.scalar;
        f = m23[1].y + scalarAfterm23;
        f = c_m23[1].y + c_scalarAfterm23;
        f += scalarBeforeArray;
        f += floatArray[2];
        f += scalarAfterArray;
        f += ablock.memvec2.x;
        f += ablock.memf1;
        f += float(ablock.memf2);
        f += ablock.memf3;
        f += ablock.memvec2a.y;
    } else
        f = ufDead3;
}
