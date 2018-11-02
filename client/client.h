#ifndef MEUDEUS_SOCKET_H
#define MEUDEUS_SOCKET_H

#include <exception>
#include <string>

namespace net {

class SocketError: public std::exception {
public:
    SocketError(std::string msg):
        msg{msg}
    {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

class Socket {
public:
    Socket(const std::string& server, std::uint16_t port);

    void open(const std::string& server, std::uint16_t port);
    void send(const std::string&);
    void close();

private:
    int _socket;
};

}

#endif
