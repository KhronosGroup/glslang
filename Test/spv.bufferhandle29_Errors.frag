#version 450

#extension GL_EXT_buffer_reference : enable

// buffer_reference_align has to be at least the largest scalar or component in the block.
layout(buffer_reference, buffer_reference_align = 2) buffer Scalar { uint x; };
layout(buffer_reference, buffer_reference_align = 4) buffer Vector { dvec2 v; };
struct S { float f; double d; };
layout(buffer_reference, buffer_reference_align = 4) buffer Nested { S s[2]; };

void main()
{
}
