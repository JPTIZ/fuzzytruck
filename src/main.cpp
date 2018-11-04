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

auto gimme_socket(const std::string& host, std::uint16_t port) {
    try {
        return net::Socket{host, port};
    } catch (const net::SocketError& e) {
        std::cerr << "Error connecting to host: " << e.what() << "\n";
        exit(-1);
    }
}

auto truck_position(net::Socket& socket) {
    auto command = "r\r\n"s;
    socket.send(command);

    auto answer = socket.listen();

    return answer;
}

int main(int argc, char* argv[]) {
    auto args = parse_args(argc, argv);
    auto socket = gimme_socket(
        args["host"s],
        std::uint16_t(std::stoi(args["port"s]))
    );

    auto truck = fuzzytruck::FunctionBlockTruck{};

    auto position = truck_position(socket);
    std::cout << "Truck answer:\n    " << position << "\n";

    truck.x = 0;
    truck.y = 0;
    truck.direction = 0;

    truck.calc();
    truck.print();
}
