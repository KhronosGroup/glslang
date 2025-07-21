#version 400
struct B
{
    vec3 t;
};

struct C
{
    vec4 u;
};

void main()
{
    // Multiple declarations in one statement
    float A, B, C; // B and C are struct names - should work
    
    // Array declarations
    int B[10], C[5]; // B and C are struct names - should work
    
    // With initializers
    vec2 B = vec2(1.0, 2.0), C = vec2(3.0, 4.0); // B and C are struct names - should work
    
    // Array with initializers
    float B[2] = float[2](1.0, 2.0), C[2] = float[2](3.0, 4.0); // B and C are struct names - should work
    
    // Nested scope
    {
        float B = 1.0; // Struct name in nested scope - should work
        int C = 42;    // Struct name in nested scope - should work
    }
} 