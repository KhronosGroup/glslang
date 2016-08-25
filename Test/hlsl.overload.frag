// function selection under type conversion
void foo1(double a, uint b)  {}
void foo1(double a, int b)   {}
void foo1(double a, float b) {}
void foo1(double a, double b){}

float4 PixelShaderFunction(float4 input) : COLOR0
{
    double d;
    uint u;
    int i;
    float f;

    foo1(d, d);
    foo1(d, u);
    foo1(d, i);
    foo1(d, f);

    foo1(f, d);
    foo1(f, u);
    foo1(f, i);
    foo1(f, f);

    foo1(u, d);
    foo1(u, u);
    foo1(u, i);
    foo1(u, f);

    foo1(i, d);
    foo1(i, u);
    foo1(i, i);
    foo1(i, f);

    return input;
}
