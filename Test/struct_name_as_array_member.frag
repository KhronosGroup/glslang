#version 400

// Test case for using a struct name as an array member name.
struct B
{
    vec3 t;
};

struct K
{
    float A[2], B[3]; // This should work - struct name B is used as an array member name.
};

void main(){}