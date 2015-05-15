#version 130

uniform sampler1D       texSampler1D;
uniform sampler2D       texSampler2D;
uniform sampler3D       texSampler3D;
uniform samplerCube	    texSamplerCube;
uniform sampler1DShadow shadowSampler1D;
uniform sampler2DShadow shadowSampler2D;

in vec2 coords2D;

void main()
{  
    float lod		 = 3.0;
    float coords1D   = 1.789;
    vec3  coords3D   = vec3(1.789, 2.718, 3.453);
    vec4  coords4D   = vec4(1.789, 2.718, 3.453, 2.0);
    vec4  color      = vec4(0.0, 0.0, 0.0, 0.0);

    color += texture1DLod(texSampler1D, coords1D, lod);
    color += texture1DProjLod(texSampler1D, coords2D, lod);
    color += texture1DProjLod(texSampler1D, coords4D, lod);
    
    color += texture2DLod     (texSampler2D, coords2D, lod);
    color += texture2DProjLod (texSampler2D, coords3D, lod);
    color += texture2DProjLod (texSampler2D, coords4D, lod);

    color += texture3DLod     (texSampler3D, coords3D, lod);
    color += texture3DProjLod (texSampler3D, coords4D, lod);
    
    color += textureCubeLod (texSamplerCube, coords3D, lod);

    color += shadow1DLod    (shadowSampler1D, coords3D, lod);
    color += shadow2DLod    (shadowSampler2D, coords3D, lod);
    color += shadow1DProjLod(shadowSampler1D, coords4D, lod);
    color += shadow2DProjLod(shadowSampler2D, coords4D, lod);

    gl_Position = color;
}
