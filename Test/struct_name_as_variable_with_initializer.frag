#version 400
struct B
{
    vec3 t;
};

void main()
{
    float B = 1.0; // Struct name as variable name with initializer - should work
    int B = 42;    // Struct name as variable name with initializer - should work
    vec2 B = vec2(1.0, 2.0); // Struct name as variable name with initializer - should work
} 