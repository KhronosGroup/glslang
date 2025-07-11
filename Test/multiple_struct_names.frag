#version 400
struct B
{
    vec3 t;
};

struct C
{
    vec4 u;
};

struct D
{
    vec2 v;
};

void main()
{
    float B, C, D; // Multiple struct names as variable names - should work
    int B[5], C[3], D[2]; // Multiple struct names as array variable names - should work
    vec2 B = vec2(1.0, 2.0), C = vec2(3.0, 4.0), D = vec2(5.0, 6.0); // Multiple struct names with initializers - should work
} 