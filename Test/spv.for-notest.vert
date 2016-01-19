#version 450
layout(location=0) out highp int r;
void main() {
  int i;
  // This infinite loop results in bad SPIR-V generated, since the merge block
  // is dropped as unreachable.  It is still useful for testing the rest of the
  // code generation.
  for (i=0; ; i++) { r = i; }
}
