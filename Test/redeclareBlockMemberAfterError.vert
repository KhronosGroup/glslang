#version 450

// Declaring gl_Position is an error, but it still takes that name at global
// scope, so gl_PerVertex can no longer be copied there. Redeclaring,
// requalifying or sizing another of its members must report errors, not
// crash.
out vec4 gl_Position;
out float gl_ClipDistance[4];
invariant gl_PointSize;
precise gl_PointSize;

void main()
{
    gl_CullDistance[0] = 1.0;
}
