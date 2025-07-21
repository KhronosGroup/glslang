#version 400
struct B
{
    vec3 t;
};

uniform float B; // Struct name as uniform variable - should work
in vec3 B;       // Struct name as input variable - should work
out vec4 B;      // Struct name as output variable - should work

void main()
{
    const float B = 1.0; // Struct name as const variable - should work
    vec4 B = vec4(1.0);  // Struct name as local variable - should work
} 