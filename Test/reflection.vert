#version 440 core

uniform nameless {
    vec3 anonMember1;
    vec4 anonDeadMember2;
    vec4 anonMember3;
};

uniform named {
    vec3 deadMember1;
    vec4 member2;
    vec4 member3;
} ablock;

uniform namelessdead {
    int a;
};

uniform namedDead {
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

void liveFunction1()
{
    liveFunction2();
    float f = uf2;
    vec4 v = ablock.member3;
}

void main()
{
    liveFunction1();
    liveFunction2();

    if (! control)
        deadFunction();

    float f;

    if (control) {
        liveFunction2();
        f = anonMember3.z;
        f = s.a;
    } else
        f = ufDead3;
}
