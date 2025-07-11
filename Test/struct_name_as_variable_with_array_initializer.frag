#version 400
struct B
{
    vec3 t;
};

void main()
{
    float B[2] = float[2](1.0, 2.0); // Struct name as array variable name with initializer - should work
    int B[3] = int[3](1, 2, 3);      // Struct name as array variable name with initializer - should work
    vec2 B[2] = vec2[2](vec2(1.0, 2.0), vec2(3.0, 4.0)); // Struct name as array variable name with initializer - should work
} 