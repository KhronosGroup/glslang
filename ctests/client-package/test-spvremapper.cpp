
#include <glslang/SPIRV/SPVRemapper.h>

void logHandler(const std::string& str) {
    std::cout << str << std::endl;
}

int main()
{
    spv::spirvbin_t::registerLogHandler(logHandler);
    return 0;
}
