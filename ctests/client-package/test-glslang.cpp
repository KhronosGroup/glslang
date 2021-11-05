
#include <glslang/build_info.h>

#include <stdio.h>
#include <string.h>

int main()
{
    char version[1024];
    sprintf(version, "%d.%d.%d", GLSLANG_VERSION_MAJOR, GLSLANG_VERSION_MINOR, GLSLANG_VERSION_PATCH);

    return strcmp(CHECK_VERSION, version) == 0 ? 0 : 1;
}
