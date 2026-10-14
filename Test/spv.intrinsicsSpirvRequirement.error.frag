#version 450 core

#extension GL_EXT_spirv_intrinsics : enable

// The requirement name and the bracketed list are parsed independently, so a
// name paired with the wrong kind of list used to dereference a null aggregate
// and crash the front end. "capabilities" with a string list, and "extensions"
// with an integer list, must be rejected with a diagnostic instead.
spirv_execution_mode(capabilities = ["SPV_bad"], 5027);
spirv_execution_mode(extensions = [5013], 5027);

void main() {}
