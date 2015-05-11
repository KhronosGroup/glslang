#version 310 es

// Check name mangling of functions with parameters that are multi-dimensional arrays.

#define NX 2
#define NY 3
#define NZ 4
void f(bool a, float b, uint[4] c, int[NY][NX] d) {
}

void main() {
  int[NY][NX] d;
  f(false, 12.1, uint[NZ](uint(0),uint(1),uint(1),uint(2)), d);
}
