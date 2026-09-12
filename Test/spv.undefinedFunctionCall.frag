#version 450

// Calling a function that is only declared, never defined, in a --no-link
// (EOptionCompileOnly) unit.
//
// GLSL has no import linkage — TLinkType is ELinkNone or ELinkExport — so the
// callee cannot be named in the SPIR-V that would come out, and spirv-link has
// no symbol to resolve. checkCallGraphBodies() reports this for a linked unit,
// but it runs from finalCheck() during link, which a compile-only unit never
// reaches; SPIR-V generation then ran on a call with no callee and segfaulted.
vec4 do_some_math(vec4 arg);

vec4 calculate_color(vec4 arg) {
    return clamp(do_some_math(arg), 0.0, 2.0) * 0.5;
}
