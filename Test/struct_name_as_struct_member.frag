#version 400
struct B
{
    vec3 t;
};

struct K
{
    float A, B; // Struct name B as member name - should work
    int B;      // Struct name B as member name - should work
    vec2 B;     // Struct name B as member name - should work
};

void main(){} 