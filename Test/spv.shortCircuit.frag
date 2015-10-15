#version 400

uniform ivec4 uiv4;
uniform vec4 uv4;
uniform bool ub;
uniform bool uba;
uniform bvec4 ub41, ub42;
uniform float uf;
uniform int ui;

out float of1;
out vec4  of4;

bool foo() { ++of1; return of1 > 10.0; }

void main()
{
    of1 = 0.0;
    of4 = vec4(0.0);

    if (ub || ui > 2)  // not worth short circuiting
        ++of1;

    if (ub && !uba)  // not worth short circuiting
        ++of1;

    if (ub || foo())   // must short circuit
        ++of1;

    if (ub && foo())   // must short circuit
        ++of1;

    if (foo() || ub)   // not worth short circuiting
        ++of1;

    if (foo() && ub)   // not worth short circuiting
        ++of1;

    if (ub || ++of1 > 1.0)   // must short circuit
        ++of4;

    if (++of1 > 1.0 || ub)   // not worth short circuiting
        ++of4;

    if (ub || sin(uf) * 4.0 > of1)  // worth short circuiting
        ++of1;

    if (ub && sin(uf) * 4.0 > of1)  // worth short circuiting
        ++of1;
}
