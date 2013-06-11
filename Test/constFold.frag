#version 430

const int a = 1;
const int b = 2;
const int c = a + b; // 3
const int d = c - a; // 2
const float e = float(d); // 2.0
const float f = e * float(c); // 6.0
const float g = f / float(d); // 3.0

const vec2 pytho = vec2(3.0, 4.0);

in vec4 inv;
out vec4 FragColor;
out vec2 out2;
out vec4 out3;
out vec4 out4;
out ivec4 out5;
out vec3 out6;
out vec4 out7;
out vec4 out8;
out vec4 out9;
   
void main()
{
    vec4 dx = dFdx(inv);
    const ivec4 v = ivec4(a, b, c, d);
    vec4 array2[v.y];                  // 2
    const ivec4 u = ~v;

    const float h = degrees(g); // 171.88

    FragColor = vec4(e, f, g, h);  // 2, 6, 3, 171.88

    vec4 array3[c];               // 3
    vec4 arrayMax[int(max(float(array2.length()), float(array3.length())))];
    vec4 arrayMin[int(min(float(array2.length()), float(array3.length())))];
    FragColor = vec4(arrayMax.length(), arrayMin.length(), sin(3.14), cos(3.14));  // 3, 2, .00159, -.999
    out2 = length(pytho) + normalize(pytho) + dFdx(pytho) + dFdy(pytho) + fwidth(pytho); // 5+3/5, 5+4/5
    out3 = vec4(exp(3.0), log(10.0), exp2(4.0), log2(256.0));  //  20.08, 2.3, 16, 8
    out4 = vec4(sqrt(100.0), inversesqrt(100.0), abs(-4.7), abs(10.9)); // 10, .1, 4.7, 10.9
    out5 = ivec4(abs(-8) + sign(0), abs(17), sign(-12), sign(9));  // 8, 17, -1, 1
    out6 = vec3(sign(-8.8), sign(18.0), sign(0.0)); // -1.0, 1.0, 0.0
    out7 = vec4(floor(4.2), ceil(-4.1), trunc(5.9), trunc(-5.9)); // 4, -4, 5, -5
    out8 = vec4(round(4.4), round(4.6), roundEven(4.5), roundEven(-5.5)); // 4, 5, 4, -6
    out9 = vec4(roundEven(7.5), roundEven(-4.5), fract(2.345), fract(-2.6)); // 8, -4, .345, 0.4
}
