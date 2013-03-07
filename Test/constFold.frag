#version 430

const int a = 1;
const int b = 2;
const int c = a + b; // 3
const int d = c - a; // 2
const float e = float(d); // 2.0
const float f = e * float(c); // 6.0
const float g = f / float(d); // 3.0

in vec4 inv;
out vec4 FragColor;

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
}
