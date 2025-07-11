#version 400
struct B
{
    vec3 t;
};

void main()
{
    float B; // Struct name as variable name - should work
    int B;   // Struct name as variable name - should work
    vec2 B;  // Struct name as variable name - should work
} 