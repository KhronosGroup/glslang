
#include <string>

// TODO: no prototype available
namespace glslang {
    std::string GetDefaultTBuiltInResourceString();
}

int main()
{
    std::string s = glslang::GetDefaultTBuiltInResourceString();

    return 0;
}
