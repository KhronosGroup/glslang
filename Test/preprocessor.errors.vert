#version 310 es

#define X

#if X
  #if Y
    #error This should not show up in pp output.
  #endif
    #error This should show up in pp output.
#else
  #error This should not show up in pp output.
#endif

int main() {
}
