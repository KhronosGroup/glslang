#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <vector>
#include "protocol.hpp"

int read_message(std::string& body)
{
    char c;
    std::string line;
    while (std::cin.get(c)) {
        line.push_back(c);
        if (line.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    auto start_pos = line.find("Content-Length: ");

	// std::cerr << "recv header: \n" << line << std::endl;
    if (start_pos == std::string::npos) {
        std::cerr << "format error: " << line << std::endl;
        return -1;
    }

    auto end_pos = line.find("\r\n\r\n");
    std::string content_length(line.begin() + start_pos, line.begin() + end_pos);

    auto length_offset = content_length.find(": ");
    std::string num(content_length.begin() + length_offset + 2, content_length.end());
    auto len = ::atoi(num.c_str());

	// std::cerr << "recv Content Length: " << content_length << std::endl << " str num: " << num << "\n int num: " << len << std::endl;

    std::vector<char> buf(len);
    auto* p = buf.data();
    int n = 0;
    int total_len = len;
    while ((n = fread(p, 1, total_len, stdin)) > 0) {
        total_len -= n;
        p += n;
        if (total_len <= 0)
            break;
    }

    body = std::string(buf.begin(), buf.end());
	// std::cerr << "recv body: \n" << body << std::endl;
    return 0;
}

static void handle_message(std::string const& body)
{
	static Protocol protocol;
	// std::cerr << "start handle message: " << std::endl << body << std::endl;
	auto json = nlohmann::json::parse(body);
	protocol.handle(json);
}

int main(int argc, char* argv[])
{
    std::string body;
    while (read_message(body) == 0) {
		handle_message(body);
		body.clear();
    };

    return 0;
}
