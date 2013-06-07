#version 300 es

uniform sampler2D s2D;
uniform sampler3D s3D;
uniform samplerCube sCube;
uniform samplerCubeShadow sCubeShadow;
uniform sampler2DShadow s2DShadow;
uniform sampler2DArray s2DArray;
uniform sampler2DArrayShadow s2DArrayShadow;

uniform isampler2D is2D;
uniform isampler3D is3D;
uniform isamplerCube isCube;
uniform isampler2DArray is2DArray;

uniform usampler2D us2D;
uniform usampler3D us3D;
uniform usamplerCube usCube;
uniform usampler2DArray us2DArray;

in float c1D;
in vec2  c2D;
in vec3  c3D;
smooth vec4  c4D;

flat in int   ic1D;
flat in ivec2 ic2D;
flat in ivec3 ic3D;
flat in ivec4 ic4D;
noperspective in vec4 badv; // ERROR
in sampler2D bads; // ERROR
precision lowp uint;       // ERROR

struct s {
    int i;
    sampler2D s;   // ERROR
};

out s badout;      // ERROR

void main()
{
    float f;
    vec4 v;
    v = texture(s2D, c2D);
    v = textureProj(s3D, c4D);
    v = textureLod(s2DArray, c3D, 1.2);
    f = textureOffset(s2DShadow, c3D, ic2D, c1D);
    v = texelFetch(s3D, ic3D, ic1D);
    v = texelFetchOffset(s2D, ic2D, 4, ic2D);
    f = textureLodOffset(s2DShadow, c3D, c1D, ic2D);
    v = textureProjLodOffset(s2D, c3D, c1D, ic2D);
    v = textureGrad(sCube, c3D, c3D, c3D);
    f = textureGradOffset(s2DArrayShadow, c4D, c2D, c2D, ic2D);
    v = textureProjGrad(s3D, c4D, c3D, c3D);
    v = textureProjGradOffset(s2D, c3D, c2D, c2D, ic2D);

    ivec4 iv;
    iv = texture(is2D, c2D);
    iv = textureProjOffset(is2D, c4D, ic2D);
    iv = textureProjLod(is2D, c3D, c1D);
    iv = textureProjGrad(is2D, c3D, c2D, c2D);
    iv = texture(is3D, c3D, 4.2);
    iv = textureLod(isCube, c3D, c1D);
    iv = texelFetch(is2DArray, ic3D, ic1D);

    iv.xy = textureSize(sCubeShadow, 2);

    float precise;
    double boo;       // ERROR
    dvec2 boo2;       // ERROR
    dvec3 boo3;       // ERROR
    dvec4 boo4;       // ERROR

    f += gl_FragCoord.y;
    gl_FragDepth = f;
}

float imageBuffer;    // ERROR, reserved
float uimage2DRect;   // ERROR, reserved
