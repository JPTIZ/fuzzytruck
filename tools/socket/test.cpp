#include "socket.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std::string_literals;

auto parse_args(int argc, char* _argv[]) {
    auto args = std::map{
        std::pair
        {"host"s, std::string(_argv[1])},
        {"port"s, std::string(_argv[2])},
    };

    return args;
}

void show_usage(const std::string& exec_name) {
    std::cout << "Usage: " << exec_name << " <host> <port>\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        show_usage(argv[0]);
        return -1;
    }

    auto args = parse_args(argc, argv);

    auto socket = net::Socket{
        args["host"s],
        std::uint16_t(std::stoi(args["port"s]))
    };

    socket.send("1\r\n");
    socket.send("1\r\n");
    socket.send("-1\r\n");
    socket.send("1\r\n");
}
