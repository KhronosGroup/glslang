#version 140

uniform isamplerBuffer sbuf;

layout(std140) uniform blockName {
    int anonMem;
};

void main()
{
    int id = gl_InstanceID;
    id += anonMem;
    id += texelFetch(sbuf, 8).w;
    gl_ClipVertex;      // could be ERROR, but compiling under compatibility profile
    gl_Color;           // could be ERROR, but compiling under compatibility profile
    gl_LightSource[0];  // could be ERROR, but compiling under compatibility profile
    gl_DepthRange.far;
    gl_TexCoord;        // could be ERROR, but compiling under compatibility profile
    gl_FogFragCoord;    // could be ERROR, but compiling under compatibility profile
    gl_FrontColor;      // could be ERROR, but compiling under compatibility profile
}

out vec4 gl_Position;  // ERROR

layout(location = 9) in vec4 locBad;  // ERROR

#extension GL_ARB_explicit_attrib_location : enable

layout(location = 9) in vec4 loc;

#extension GL_ARB_separate_shader_objects : enable

out vec4 gl_Position;
in vec4 gl_Position;   // ERROR
out vec3 gl_Position;  // ERROR

out float gl_PointSize;
out vec4 gl_ClipVertex;
out float gl_FogFragCoord;
