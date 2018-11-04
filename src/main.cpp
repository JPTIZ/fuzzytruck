#include <iostream>
#include <map>

#include "../fuzzytruck/truck.h"
#include "../tools/socket/socket.h"

using namespace std::string_literals;

void show_usage(const std::string& exec_name) {
    std::cout << "Usage: " << exec_name << " <host> <port>\n";
}

auto parse_args(int argc, char* argv[]) {
    if (argc < 3) {
        show_usage(argv[0]);
        exit(-1);
    }

    auto args = std::map{
        std::pair
        {"host"s, std::string(argv[1])},
        {"port"s, std::string(argv[2])},
    };

    return args;
}

int main(int argc, char* argv[]) {
    auto args = parse_args(argc, argv);

    try {
        auto socket = net::Socket{
            args["host"s],
            std::uint16_t(std::stoi(args["port"s]))
        };
    } catch (const net::SocketError& e) {
        std::cerr << "Error connecting to host: " << e.what() << "\n";
    }

    auto truck = fuzzytruck::FunctionBlockTruck{};

    truck.x = 1;
    truck.y = 0;
    truck.angle = 0;

    truck.calc();
    truck.print();
}
