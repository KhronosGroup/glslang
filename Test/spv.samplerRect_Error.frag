#version 460

uniform sampler2DRect samp1;
uniform sampler2DRectShadow samp2;
uniform isampler2DRect samp3;
uniform usampler2DRect us2Dr;

layout(rgba8) uniform image2DRect i2Dr;
layout(rg16ui) uniform uimage2DRect ui2Dr;
layout(r32i) uniform iimage2DRect ii2Dr;

void main() { }
