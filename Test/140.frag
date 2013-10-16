#version 140

varying vec4 v;

in vec4 i;
out vec4 o;

in float gl_ClipDistance[5];

void main()
{
    float clip = gl_ClipDistance[2];
}
#ifdef GL_ES
#error GL_ES is set
#else
#error GL_ES is not set
#endif
