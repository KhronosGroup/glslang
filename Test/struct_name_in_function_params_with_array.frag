#version 400
struct B
{
    vec3 t;
};

void func(float B[5], int B[3], vec2 B[2]) // Struct name B as array parameter names - should work
{
    // Function body
}

void main()
{
    float arr1[5] = float[5](1.0, 2.0, 3.0, 4.0, 5.0);
    int arr2[3] = int[3](1, 2, 3);
    vec2 arr3[2] = vec2[2](vec2(1.0, 2.0), vec2(3.0, 4.0));
    func(arr1, arr2, arr3);
} 