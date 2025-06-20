#include "protocol.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

int main(int argc, char* argv[])
{
    int ch = -1;
    std::vector<std::string> files;
    while ((ch = ::getopt(argc, argv, "f:")) != -1) {
        switch (ch) {
        case 'f':
            files.push_back(optarg);
            continue;
        default:
            break;
        }
    }

    if (files.empty()) {
        fprintf(stderr, "input 0 files\n");
        return -1;
    }

    static Protocol protocol;

    for (auto const& f : files) {
        std::ifstream ifs(f);
        nlohmann::json body = nlohmann::json::parse(ifs);
		protocol.handle(body);
    }

    return 0;
}
