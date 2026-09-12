#version 450

#extension GL_EXT_buffer_reference : enable

layout(buffer_reference, std430) buffer BlockA { float a; };
layout(buffer_reference, std430) buffer BlockB { uint b; };
layout(buffer_reference) buffer Node;
layout(buffer_reference, std430) buffer Node { int v; Node next; };

layout(set = 0, binding = 0) uniform Handles {
    BlockA pa;
    BlockB pb;
    Node   pn;
} handles;

struct WrapA { BlockA p; };
struct WrapB { BlockB p; };

// Overloads that differ only in which buffer reference type they take.
float f(BlockA p) { return p.a; }
float f(BlockB p) { return float(p.b); }

// The same, one level down, where the reference is a struct member.
float g(WrapA w) { return w.p.a; }
float g(WrapB w) { return float(w.p.b); }

// A block that names itself still has to produce a finite mangled name.
float h(Node n) { return float(n.next.v); }

layout(location = 0) out float o;

void main()
{
    o = f(handles.pa) + f(handles.pb)
      + g(WrapA(handles.pa)) + g(WrapB(handles.pb))
      + h(handles.pn);
}
