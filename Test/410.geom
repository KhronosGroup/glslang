#version 410 core

void main()
{
    gl_ViewportIndex = 7;
}

in gl_PerVertex {
    float gl_PointSize;
} myIn[];  // ERROR, can't redeclare a different name

in gl_PerVertex {
    float gl_PointSize;
} gl_myIn[];  // ERROR, can't redeclare a different name

in gl_PerVertex {
    float gl_PointSize;
} gl_in[];

in gl_PerVertex {
    float gl_PointSize;
} gl_in[];     // ERROR, can't do it again

out gl_PerVertex {
    float gl_PointSize;
};

void foo()
{
    float p = gl_in[1].gl_PointSize;   // use of redeclared
    gl_PointSize = p;   // use of redeclared
}
