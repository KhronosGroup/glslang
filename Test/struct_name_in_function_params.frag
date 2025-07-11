#version 400
struct B
{
    vec3 t;
};

void func(float B, int B, vec2 B) // Struct name B as parameter names - should work
{
    // Function body
}

void main()
{
    func(1.0, 42, vec2(1.0, 2.0));
} 