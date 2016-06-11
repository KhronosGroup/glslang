struct {
};

struct {
    bool b;
};

struct myS {
    bool b, c;
    float4 a, d;
};

myS s1;

struct {
    float4 i;
} s2;

float4 PixelShaderFunction(float4 input) : COLOR0
{
    struct FS {
        bool3 b3;
    } s3;

    s3 == s3;
}