#version 450

#extension GL_EXT_dynamically_uniform_attribute : enable

[[dynamically_uniform]] int foo([[dynamically_uniform]] int x) {
  return x;
}

void main() {
  {
    int x = 42;
    int y;
    int z[4];
    int w[1] = {42};
  }

  {
    [[dynamically_uniform]] int x = 42;
    [[dynamically_uniform]] int y;
    [[dynamically_uniform]] int z[4];
    [[dynamically_uniform]] int w[1] = {42};

    y = 13;
    z[0] = foo(y);
  }
}
