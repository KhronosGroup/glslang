#version 400
struct B
{
    vec3 t;
};

void main()
{
    float B[10]; // Struct name as array variable name - should work
    int B[5];    // Struct name as array variable name - should work
    vec2 B[3];   // Struct name as array variable name - should work
} 