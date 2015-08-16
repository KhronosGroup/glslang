#version 310 es
highp float nodef3(float); // ERROR, no default precision
precision mediump float;
precision highp usampler2D;
precision highp sampler2D;
precision highp isampler2DArray;

layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;  // ERROR, not supported

layout(location = 2) in vec3 v3;
layout(location = 2) in mat4 yi;  // ERROR, locations conflict with xi

uniform sampler2D arrayedSampler[5];
uniform usampler2D usamp2d;
uniform usampler2DRect samp2dr;      // ERROR, reserved
uniform isampler2DArray isamp2DA;

in vec2 c2D;
uniform int i;

void main()
{
    vec4 v = texture(arrayedSampler[i], c2D);  // ERROR

    ivec2 offsets[4];
    const ivec2 constOffsets[4] = ivec2[4](ivec2(1,2), ivec2(3,4), ivec2(15,16), ivec2(-2,0));
    uvec4 uv4 = textureGatherOffsets(samp2dr, c2D, offsets, 2);  // ERROR, not supported
    vec4 v4 = textureGather(arrayedSampler[0], c2D);
    ivec4 iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 3);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), i);  // ERROR, last argument not const
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 4);  // ERROR, last argument out of range
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(1), 1+2);
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(0.5));
    iv4 = textureGatherOffset(isamp2DA, vec3(0.1), ivec2(i));     // ERROR, offset not constant
}

out vec4 outp;
void foo23()
{
    const ivec2[3] offsets = ivec2[3](ivec2(1,2), ivec2(3,4), ivec2(15,16));

    textureProjGradOffset(usamp2d, outp, vec2(0.0), vec2(0.0), ivec2(c2D));     // ERROR, offset not constant
    textureProjGradOffset(usamp2d, outp, vec2(0.0), vec2(0.0), offsets[1]);
    textureProjGradOffset(usamp2d, outp, vec2(0.0), vec2(0.0), offsets[2]);     // ERROR, offset out of range
    textureProjGradOffset(usamp2d, outp, vec2(0.0), vec2(0.0), ivec2(-10, 20)); // ERROR, offset out of range

    if (gl_HelperInvocation)
        ++outp;

    int sum = gl_MaxVertexImageUniforms +
              gl_MaxFragmentImageUniforms +
              gl_MaxComputeImageUniforms +
              gl_MaxCombinedImageUniforms +
              gl_MaxCombinedShaderOutputResources;

    bool b1, b2, b3, b;

    b1 = mix(b2, b3, b);
    uvec3 um3 = mix(uvec3(i), uvec3(i), bvec3(b));
    ivec4 im4 = mix(ivec4(i), ivec4(i), bvec4(b));
}

layout(binding=3) uniform sampler2D s1;
layout(binding=3) uniform sampler2D s2; // ERROR: overlapping bindings?  Don't see that in the 310 spec.
layout(binding=2) uniform writeonly image2D      i2D;
layout(binding=4) uniform readonly  image3D      i3D;
layout(binding=5) uniform           imageCube    iCube;
layout(binding=6) uniform           image2DArray i2DA;
layout(binding=6) uniform coherent volatile restrict image2D i2Dqualified;

layout(binding = 1) uniform bb {
    int foo;
    layout(binding = 2) float f;     // ERROR
} bbi;

in centroid vec4 centroidIn;
layout(location = 200000) uniform vec4 bigl;  // ERROR, location too big

layout(early_fragment_tests) in;

layout(location = 40) out vec4 bigout1;  // ERROR, too big
layout(location = 40) out vec4 bigout2;  // ERROR, overlap
layout(location = -2) out vec4 neg;      // ERROR, negative

layout(std430) buffer b430 {
    int i;
} b430i;

layout(shared) uniform bshar {
    int i;
} bshari;

in smooth vec4 smoothIn;
in flat int flatIn;

uniform sampler2DMS s2dms;

void foots()
{
    highp ivec2 v2 = textureSize(s1, 2);
    highp ivec3 v3 = textureSize(isamp2DA, 3);
    v2 = textureSize(s2dms);
    v2 = imageSize(i2D);
    v3 = imageSize(i3D);
    v2 = imageSize(iCube);
    v3 = imageSize(i2DA);
    v2 = imageSize(i2Dqualified);
}

out bool bout;          // ERROR
out image2D imageOut;   // ERROR
out mat2x3 mout;        // ERROR

in bool inb;         // ERROR
in sampler2D ino;    // ERROR
in float ina[4];
in float inaa[4][2]; // ERROR
struct S { float f; };
in S ins;
in S[4] inasa;       // ERROR
in S insa[4];        // ERROR
struct SA { float f[4]; };
in SA inSA;          // ERROR
struct SS { float f; S s; };
in SS inSS;          // ERROR

#ifndef GL_EXT_shader_io_blocks
#error GL_EXT_shader_io_blocks not defined
#endif

#extension GL_EXT_shader_io_blocks : enable

out outbname { int a; } outbinst;   // ERROR, not out block in fragment shader

in inbname {
    int a;
    vec4 v;
    struct { int b; } s;     // ERROR, nested struct definition
} inbinst;

in inbname2 {
    layout(location = 12) int aAnon;
    layout(location = 13) centroid in vec4 vAnon;
};

in layout(location = 13) vec4 aliased; // ERROR, aliased

in inbname2 {                // ERROR, reuse of block name
    int aAnon;
    centroid in vec4 vAnon;
};

in badmember {               // ERROR, aAnon already in global scope
    int aAnon;
};

int inbname;                 // ERROR, redefinition of block name

vec4 vAnon;                  // ERROR, anon in global scope; redefinition

in arrayed {
    float f;
} arrayedInst[4];

void fooIO()
{
    vec4 v = inbinst.v + vAnon;
    v *= arrayedInst[2].f;
    v *= arrayedInst[i].f;       // ERROR, not constant
}

in vec4 gl_FragCoord;
layout(origin_upper_left, pixel_center_integer) in vec4 gl_FragCoord;  // ERROR, non-ES

layout(early_fragment_tests) in;
out float gl_FragDepth;
layout(depth_any) out float gl_FragDepth;  // ERROR, non-ES

void foo_IO()
{
    gl_FragDepth = 0.2;  // ERROR, early_fragment_tests declared
    gl_Layer;            // ERROR, not present
    gl_PrimitiveID;      // ERROR, not present
    bool f = gl_FrontFacing;
}

out float gl_FragDepth;

#extension GL_OES_geometry_shader : enable

void foo_GS()
{
    highp int l = gl_Layer;
    highp int p = gl_PrimitiveID;
}

in vec2 inf, ing;
uniform ivec2 offsets[4];
uniform sampler2D sArray[4];
uniform int sIndex;
layout(binding = 0) uniform atomic_uint auArray[2];
uniform ubName { int i; } ubInst[4];
buffer bbName { int i; } bbInst[4];
uniform writeonly image2D iArray[5];
const ivec2 constOffsets[4] = ivec2[4](ivec2(0.1), ivec2(0.2), ivec2(0.3), ivec2(0.4));

void pfooBad()
{
    precise vec2 h;                                            // ERROR reserved
    h = fma(inf, ing, h);                                      // ERROR, not available
    textureGatherOffset(sArray[0], vec2(0.1), ivec2(inf));     // ERROR, offset not constant
    textureGatherOffsets(sArray[0], vec2(0.1), constOffsets);  // ERROR, not available
}

#extension GL_OES_gpu_shader5 : enable

void pfoo()
{
    precise vec2 h;
    h = fma(inf, ing, h);
    textureGatherOffset(sArray[0], vec2(0.1), ivec2(inf));
    textureGatherOffsets(sArray[0], vec2(0.1), constOffsets);
    textureGatherOffsets(sArray[0], vec2(0.1), offsets);       // ERROR, offset not constant
}

#extension GL_EXT_texture_cube_map_array : enable

precision highp imageCubeArray        ;
precision highp iimageCubeArray       ;
precision highp uimageCubeArray       ;

precision highp samplerCubeArray      ;
precision highp samplerCubeArrayShadow;
precision highp isamplerCubeArray     ;
precision highp usamplerCubeArray     ;

uniform writeonly imageCubeArray  CA1;
uniform writeonly iimageCubeArray CA2;
uniform writeonly uimageCubeArray CA3;

#ifdef GL_EXT_texture_cube_map_array
uniform samplerCubeArray          CA4;
uniform samplerCubeArrayShadow    CA5;
uniform isamplerCubeArray         CA6;
uniform usamplerCubeArray         CA7;
#endif

void CAT()
{
    highp vec4 b4 = texture(CA4, vec4(0.5), 0.24);
    highp ivec4 b6 = texture(CA6, vec4(0.5), 0.26);
    highp uvec4 b7 = texture(CA7, vec4(0.5), 0.27);
}
