#version 400
struct B
{
    vec3 t;
};

struct K
{
    float A, B[10]; // Struct name B as array member name - should work
    int B[5];       // Struct name B as array member name - should work
    vec2 B[3];      // Struct name B as array member name - should work
};

void main(){} 