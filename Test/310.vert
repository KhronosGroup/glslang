#version 310 es

shared vec4 s;   // ERROR
layout(local_size_x = 2) out;  // ERROR
buffer vec4 v;  // ERROR

layout(location = 2) uniform mat4 x;
layout(location = 3) uniform mat4 y;
layout(location = 2) out mat4 xi;
layout(location = 3) out mat4 yi;  // ERROR, locations conflict with xi
