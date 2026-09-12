#version 450

// A prototype resolved later in the same unit is not an undefined callee. The
// end-of-parse check collects every definition in the unit before reporting.
vec4 later(vec4 a);

vec4 caller(vec4 a) {
    return later(a);
}

vec4 later(vec4 a) {
    return a * 3.0;
}
