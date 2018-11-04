#include "socket.h"

#include <netdb.h>
#include <sys/socket.h>
#include <sys/unistd.h>

using addrinfo_t = struct addrinfo;

using namespace std::string_literals;

namespace {

void fail(const std::string& host, std::uint16_t port, int code) {
    auto err_msg = "Unknown error "s + std::to_string(code);

    switch (code) {
    case ECONNREFUSED:
        err_msg = "Connection refused.";
        break;
    case EACCES:
        err_msg = "Permission deined.";
        break;
    case EADDRINUSE:
        err_msg = "Address in use.";
        break;
    case ETIMEDOUT:
        err_msg = "Timeout.";
        break;
    case ENOTSOCK:
        err_msg = "File Descriptor is not a socket.";
    };

    throw net::SocketError(err_msg);
}

}

namespace net {

Socket::Socket(const std::string& host, std::uint16_t port) {
    open(host, port);
}


void Socket::open(const std::string& host, std::uint16_t port) {
    auto host_info = addrinfo_t{
        .ai_family = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM,
    };
    auto results = (addrinfo_t*){};

    getaddrinfo(
        host.c_str(),
        std::to_string(port).c_str(),
        &host_info,
        &results
    );

    auto result = results[0];

    _socket = socket(
        result.ai_family,
        result.ai_socktype,
        result.ai_protocol
    );

    if (connect(_socket, result.ai_addr, result.ai_addrlen) < 0) {
        fail(host, port, errno);
    }
}


void Socket::send(const std::string& msg) {
    ::send(_socket, msg.c_str(), msg.size(), 0);
}


void Socket::close() {
    ::close(_socket);
}

}
