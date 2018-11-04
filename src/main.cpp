#include <iostream>
#include <sstream>
#include <string>
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

auto parse_double(const std::string& s) {
    auto i = std::istringstream{s};
    double d;
    i >> d;
    return d;
}

auto parse_position(const std::string& s) {
    auto x_end = s.find('\t');
    auto x = parse_double(s.substr(0, x_end));

    auto y_end = s.find('\t', x_end+1);
    auto y = parse_double(s.substr(x_end+1, y_end));

    auto angle = parse_double(s.substr(y_end+1));

    return std::tuple{x, y, angle};
}

auto truck_position(net::Socket& socket) {
    auto command = "r\r\n"s;
    socket.send(command);

    auto answer = socket.listen();

    return parse_position(answer);
}

int main(int argc, char* argv[]) {
    auto args = parse_args(argc, argv);
    auto socket = gimme_socket(
        args["host"s],
        std::uint16_t(std::stoi(args["port"s]))
    );

    auto truck = fuzzytruck::FunctionBlockTruck{};

    while (true) {
        auto [x, y, angle] = truck_position(socket);
        if (x < 0 or x > 1 or y < 0 or y > 1) {
            break;
        }
        truck.x = x;
        truck.y = y;
        truck.direction = angle;

        truck.calc();
        truck.print();

        auto action = truck.action;
    }
}
