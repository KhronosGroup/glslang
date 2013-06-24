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
