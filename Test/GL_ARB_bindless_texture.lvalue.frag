#version 460 core

#extension GL_ARB_bindless_texture: require

// These two are declared before any other bindless construct in the file, so only
// the extension itself can enable the opaque out and inout parameters.
void setSampler(out sampler2D s, uvec2 handle)
{
    s = sampler2D(handle);
}

void copyBuffers(inout samplerBuffer bufs[2], samplerBuffer src)
{
    bufs[0] = src;
    bufs[1] = src;
}

uniform sampler2D tex;
uniform samplerBuffer buf;
uniform uvec2 handle;
uniform vec2 coord;
layout(rgba8) uniform image2D img;

out vec4 color0;
out vec4 color1;
out uvec2 handleOut;

void main()
{
    sampler2D local = tex;                      // sampler as a temporary
    setSampler(local, handle);                  // written through an out parameter
    color0 = texture(local, coord);

    samplerBuffer bufs[2];
    copyBuffers(bufs, buf);                     // array of samplers through inout
    color1 = texelFetch(bufs[1], 0);

    image2D localImage = img;                   // images are handles too
    color1 += imageLoad(localImage, ivec2(0, 0));

    handleOut = uvec2(tex);                     // handle out of a sampler
}
