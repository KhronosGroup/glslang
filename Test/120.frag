#version 120

float lowp;
float mediump;
float highp;

float precision;

in vec4 i;
out vec4 o;

uniform sampler2D s2D;
centroid varying vec2 centTexCoord;

uniform mat4x2 m;

struct s {
    float f;
};

void main()
{
    mat2x3 m23 = mat2x3(m);

    int a;
    bool b;
    s sv = s(a);
    float[2] ia = float[2](3, i.y);
    float f1 = 1;
    float f = a;
    f = a;
    ivec3 iv3;
    vec3 v3 = iv3;
    f = f + a;
    f = a - f;
    f += a;
    f = a - f;
    v3 *= iv3;
    v3 = iv3 / 2.0f;
    v3 = 3.0 * iv3;
    v3 = 2 * v3;
    v3 = v3 - 2;
    if (f <  a ||
        a <= f ||
        f >  a ||
        f >= a ||
        a == f ||
        f != a);
    f = b ? a : f;
    f = b ? f : a;
    f = b ? a : a;
    s news = sv;
    
    i.xy + i.xyz;      // ERROR
    m * i.xyz;         // ERROR
    m + i;             // ERROR
    int aoeu = 1.0;    // ERROR
    f = b;             // ERROR
    f = a + b;         // ERROR
    f = b * a;         // ERROR
    b = a;             // ERROR
    b = b + f;         // ERROR
    f |= b;            // ERROR

    gl_FragColor = texture2D(s2D, centTexCoord);

    float flat;
    float smooth;
    float noperspective;
    float uvec2;
    float uvec3;
    float uvec4;
    //packed;     // ERROR, reserved word

    {
        mat4 m;
        vec4 v;
        bool b;
        gl_FragColor += b ? v : m;  // ERROR, types don't match around ":"
    }

    gl_FragColor.xr;    // ERROR, swizzlers not from same field space
    gl_FragColor.xyxyx.xy; // ERROR, cannot make a vec5, even temporarily
    centTexCoord.z;     // ERROR, swizzler out of range
    (a,b) = true;       // ERROR, not an l-value
}

float imageBuffer;
float uimage2DRect;

int main() {}           // ERROR
void main(int a) {}     // ERROR

const int a;            // ERROR

int foo(in float a);
int foo(out float a)    // ERROR
{
    return 3.2;         // ERROR
    foo(a);             // ERROR
}

bool gen(vec3 v)
{
    if (abs(v[0]) < 1e-4F && abs(v[1]) < 1e-4)
        return true;
}

void v1()
{
}

void v2()
{
    return v1();  // ERROR, no expression allowed, even though void
}

void atest()
{
    vec4 v = gl_TexCoord[1];
    v += gl_TexCoord[3];
}

varying vec4 gl_TexCoord[6];  // okay, assigning a size
varying vec4 gl_TexCoord[5];  // ERROR, changing size

mat2x2 m22;
mat2x3 m23;
mat2x4 m24;

mat3x2 m32;
mat3x3 m33;
mat3x4 m34;

mat4x2 m42;
mat4x3 m43;
mat4x4 m44;

void foo123()
{
    mat2 r2 = matrixCompMult(m22, m22);
    mat3 r3 = matrixCompMult(m33, m33);
    mat4 r4 = matrixCompMult(m44, m44);

    mat2x3 r23 = matrixCompMult(m23, m23);
    mat2x4 r24 = matrixCompMult(m24, m24);
    mat3x2 r32 = matrixCompMult(m32, m32);
    mat3x4 r34 = matrixCompMult(m34, m34);
    mat4x2 r42 = matrixCompMult(m42, m42);
    mat4x3 r43 = matrixCompMult(m43, m43);

    mat3x2 rfoo1 = matrixCompMult(m23, m32);  // ERROR
    mat3x4 rfoo2 = matrixCompMult(m34, m44);  // ERROR    
}
