#version 440

// Note 'location'-only tests for enhanced layouts are in 330.frag
// Generic 'component' tests are in 440.vert

// a consumes components 2 and 3 of location 4
layout(location = 4, component = 2) in vec2 a; 

// b consumes component 1 of location 4
layout(location = 4, component = 1) in float b; 
layout(location = 4, component = 2) in vec2 h;  // ERROR, component overlap not okay for fragment in

layout(location = 3, component = 2) in vec3 c;  // ERROR: c overflows components 2 and 3

// e consumes beginning (components 0, 1 and 2) of each of 6 slots
layout(location = 20, component = 0) in vec3 e[6];

// f consumes last component of the same 6 slots 
layout(location = 20, component = 3) in float f[6];

layout(location = 30, component = 3) out int be;
layout(location = 30, component = 0) out vec3 bf;  // ERROR, not the same basic type
