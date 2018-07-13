#version 460

float f;
float h3 = 3.0;

float bar()
{
    h3 *= f;
    float g3 = 2 * h3;
    return h3 + g3 + gl_FragCoord.y;
}
