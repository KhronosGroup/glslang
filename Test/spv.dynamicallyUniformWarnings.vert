#version 450

#extension GL_EXT_dynamically_uniform_attribute : enable

int foo([[dynamically_uniform]] int x) {
  return x;
}

int bar(int x) {
  return x;
}

[[dynamically_uniform]] int yar(int x) {
  // check that returning an unknown uniform value to a dynamically uniform
  // return value is a warning
  return x;
}

[[dynamically_uniform]] double har(float x) {
  // check that returning an unknown uniform value that was implicitly converted
  // to a dynamically uniform return value is a warning
  return x;
}

struct Type {
  int a;
  float b;
};

layout(set = 0, binding = 0) uniform UniformBlock {
  int uniformThing[6];
};

void main() {
  // check that constant (and thus implicitly dynamically uniform) doesn't warn
  foo(0);

  // check that storing something that isn't known to be dynamically uniform
  // into a dynamically uniform value is a warning
  [[dynamically_uniform]] int x = bar(0);

  // check that passing something that isn't dynamically uniform into a function
  // that assumes dynamically uniform is a warning
  int y = 42;
  foo(y);

  // check that assigning something of unknown uniformity to a dynamically
  // uniform value is a warning
  x = y;

  // check that assigning a constant to a dynamically uniform value doesn't warn
  x = 42;

  // check that passing something that isn't dynamically uniform and isn't even
  // a variable into a function that assumes dynamically uniform is a warning
  foo(bar(3));

  // check that dynamically uniform + unknown uniform is a warning
  foo(y * x);

  // check that dynamically uniform + constant doesn't warn
  foo(x + 42);

  // check that dynamically uniform + dynamically uniform doesn't warn
  [[dynamically_uniform]] int z = 13;
  foo(x + z);

  // check that a unary operation on a dynamically uniform is still dynamically
  // uniform so doesn't warn
  foo(~x);

  // check that a conversion on a dynamically uniform is still dynamically
  // uniform so doesn't warn
  [[dynamically_uniform]] float w = 42.0f;
  foo(int(w));

  // check that a dynamically uniform conversion result in a binary operator
  // with a unknown uniform is a warning
  foo(int(w) / y);

  // check that dynamically uniform loop index doesn't warn
  for ([[dynamically_uniform]] int i = 0; i < 10; i++) {
    foo(i);
  }

  // check that an unknown uniformity condition on a ternary results in a
  // warning
  [[dynamically_uniform]] int a = y < 4 ? z : 42;

  // check that an unknown uniformity true value results in a warning
  a = har(w) < 0.0 ? y : 42;

  // check that an unknown uniformity false value results in a warning
  a = w < 0.0f ? 42 : y;

  // check that initializing a dynamically uniform array with dynamically
  // uniform values doesn't warn
  [[dynamically_uniform]] int b[2] = {42, x};

  // check that assigning to a dynamically uniform array element with a value of
  // unknown uniformity results in a warning
  b[0] = y;

  // check that initializing a dynamically uniform array with a value of
  // unknown uniformity results in a warning
  [[dynamically_uniform]] int c[2] = {42, y};

  // check that assigning to a dynamically uniform array element with a value
  // that is dynamically uniform doesn't warn
  c[1] = x;

  // check that initializing a dynamically uniform struct with dynamically
  // uniform values doesn't warn
  [[dynamically_uniform]] Type d = {x, 42.0f};

  // check that assigning to a dynamically uniform struct element with a value
  // of unknown uniformity results in a warning
  d.a = y;

  // check that initializing a dynamically uniform struct with a value of
  // unknown uniformity results in a warning
  [[dynamically_uniform]] Type e = {y, 42.0f};

  // check that assigning to a dynamically uniform struct element with a value
  // that is dynamically uniform doesn't warn
  e.a = x;

  // check that constructing a dynamically uniform vector from dynamically
  // uniform elements doesn't warn
  [[dynamically_uniform]] ivec2 f = ivec2(x, x);

  // check that assigning something with unknown uniformity to a dynamically
  // uniform vector results in a warning
  f.yx = ivec2(y, y);

  // check that constructing a dynamically uniform vector from unknown
  // uniformity elements results in a warning
  [[dynamically_uniform]] ivec3 g = ivec3(y, x, 42);

  // check that assigning a dynamically uniform vector doesn't warn
  g.zyx = g.xzy;

  // check that h doesn't accidentally inherit dynamic uniformity
  ivec3 h = ivec3(x, x, 42);
  h.x = y;

  // check that i doesn't accidentally inherit dynamic uniformity
  Type i = Type(x, 42.0f);

  // check that j doesn't accidentally inherit dynamic uniformity
  int j[3] = int[3](x, 42, x);

  // check that a UBO is dynamically uniform and doesn't warn
  x = uniformThing[0];

  // check that indexing a UBO with an unknown uniformity index and assigning
  // that to a dynamically uniform value is a warning
  x = uniformThing[y];
}
