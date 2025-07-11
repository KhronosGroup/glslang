#version 400
struct B
{
    vec3 t;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 B; // Struct name as output variable - should work

void main()
{
    float B = 1.0; // Struct name as local variable - should work
    vec3 B = normal; // Struct name as local variable - should work
    gl_Position = vec4(position, 1.0);
} 