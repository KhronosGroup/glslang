#version 450

#extension GL_NV_shader_texture_footprint : require

layout (location = 0) in vec2 P2;
layout (location = 2) in vec3 P3;
layout (location = 3) in flat int granularity;
layout (location = 4) in float lodClamp;
layout (location = 5) in float lod;
layout (location = 6) in vec2 dx;
layout (location = 8) in vec2 dy;
layout (location = 9) in float bias;

layout (binding = 0) uniform isampler2D isample2D;
layout (binding = 1) uniform usampler2D usample2D;
layout (binding = 2) uniform isampler3D isample3D;
layout (binding = 3) uniform usampler3D usample3D;

layout (location = 0) out uint hits;
layout (location = 1) out uint lods;

void main()
{
    gl_TextureFootprint2DNV fp2D;
    gl_TextureFootprint3DNV fp3D;

    hits = 0u;
    hits += uint(textureFootprintNV(isample2D, P2, granularity, true, fp2D));
    hits += uint(textureFootprintNV(usample2D, P2, granularity, true, fp2D));
    hits += uint(textureFootprintNV(isample2D, P2, granularity, true, fp2D, bias));
    hits += uint(textureFootprintNV(usample2D, P2, granularity, true, fp2D, bias));
    hits += uint(textureFootprintClampNV(isample2D, P2, lodClamp, granularity, true, fp2D));
    hits += uint(textureFootprintClampNV(usample2D, P2, lodClamp, granularity, true, fp2D));
    hits += uint(textureFootprintClampNV(isample2D, P2, lodClamp, granularity, true, fp2D, bias));
    hits += uint(textureFootprintClampNV(usample2D, P2, lodClamp, granularity, true, fp2D, bias));
    hits += uint(textureFootprintLodNV(isample2D, P2, lod, granularity, true, fp2D));
    hits += uint(textureFootprintLodNV(usample2D, P2, lod, granularity, true, fp2D));
    hits += uint(textureFootprintGradNV(isample2D, P2, dx, dy, granularity, true, fp2D));
    hits += uint(textureFootprintGradNV(usample2D, P2, dx, dy, granularity, true, fp2D));
    hits += uint(textureFootprintGradClampNV(isample2D, P2, dx, dy, lodClamp, granularity, true, fp2D));
    hits += uint(textureFootprintGradClampNV(usample2D, P2, dx, dy, lodClamp, granularity, true, fp2D));

    hits += uint(textureFootprintNV(isample3D, P3, granularity, true, fp3D));
    hits += uint(textureFootprintNV(usample3D, P3, granularity, true, fp3D));
    hits += uint(textureFootprintNV(isample3D, P3, granularity, true, fp3D, bias));
    hits += uint(textureFootprintNV(usample3D, P3, granularity, true, fp3D, bias));
    hits += uint(textureFootprintClampNV(isample3D, P3, lodClamp, granularity, true, fp3D));
    hits += uint(textureFootprintClampNV(usample3D, P3, lodClamp, granularity, true, fp3D));
    hits += uint(textureFootprintClampNV(isample3D, P3, lodClamp, granularity, true, fp3D, bias));
    hits += uint(textureFootprintClampNV(usample3D, P3, lodClamp, granularity, true, fp3D, bias));
    hits += uint(textureFootprintLodNV(isample3D, P3, lod, granularity, true, fp3D));
    hits += uint(textureFootprintLodNV(usample3D, P3, lod, granularity, true, fp3D));

    lods = fp2D.lod + fp3D.lod;
}
