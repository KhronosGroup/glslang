#version 310 es

precision mediump float;

void fooConst(const in float f, const in highp float g)
{
}

void main()
{
    float aM, bM;
    highp float aH, bH;
    fooConst(aM, bM);   // must copy bM
    fooConst(aH, bH);   // must copy aH
}
