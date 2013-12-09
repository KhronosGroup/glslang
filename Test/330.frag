#version 330 compatibility

in vec4 inVar;
out vec4 outVar;

varying vec4 varyingVar;

void main()
{
    gl_FragColor = varyingVar;  // link ERROR: user output was used
    gl_FragData[1] = inVar;     // link ERROR: user output was used
    int buffer = 4;
}

#extension GL_ARB_separate_shader_objects : enable

in gl_PerFragment {
    vec4 gl_Color;
};

void foo()
{
    vec4 c = gl_Color;
    outVar = inVar;
}

in gl_block { // ERROR
    int gl_i;
} gl_name;

in myBlock {
    int gl_i;  // ERROR
} gl_name;     // ERROR

in gl_PerVertex {  // ERROR
    vec4 gl_FragCoord;
} gl_in[];

in gl_PerVertex {  // ERROR
    vec4 gl_FragCoord;
};  // ERROR
