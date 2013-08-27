#version 420 core

varying vec2 v2;               // ERROR, varying reserved
in vec4 bad[10];
highp in vec4 badorder;
out invariant vec4 badorder2;
in centroid vec4 badorder4;    // ERROR, no centroid input to vertex stage
out flat vec4 badorder3;
void bar(in const float a);
void bar2(highp in float b);
smooth flat out vec4 rep;      // ERROR, replicating interpolation qualification
centroid sample out vec4 rep2; // ERROR, replicating auxiliary qualification
in uniform vec4 rep3;          // ERROR, replicating storage qualification

void main()
{
    int i;
    if (i == 3)
        int j = i;
    else
        int k = j;              // ERROR, j is undeclared
    int m = k;                  // ERROR, k is undeclared
    int n = j;                  // ERROR, j is undeclared

    while (true)
        int jj;
    int kk = jj;                // ERROR, jj is undeclared
}

void bar(in highp volatile vec4 v)
{
}