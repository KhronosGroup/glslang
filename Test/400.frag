#version 330 core

in vec2 c2D;
flat in int i;

uniform sampler2D arrayedSampler[5];

void main()
{
    vec4 v;
    v = texture(arrayedSampler[i], c2D);
}
