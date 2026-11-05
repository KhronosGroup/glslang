#version 450

#extension GL_EXT_buffer_reference : enable

// Vectors and arrays count their component size, so these alignments are enough.
layout(buffer_reference, buffer_reference_align = 4) buffer Vec { vec4 v; uint x[3]; };
layout(buffer_reference, buffer_reference_align = 8) buffer Wide { double d; Vec p; };

layout(set = 0, binding = 0) buffer Root { Wide w; };

layout(location = 0) out vec4 o;

void main()
{
    o = w.p.v + vec4(float(w.d) + float(w.p.x[2]));
}
