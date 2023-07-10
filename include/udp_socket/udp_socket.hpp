#ifndef UDP_SOCKET_HPP_
#define UDP_SOCKET_HPP_

#include <string>

class UDPSocket {
public:

    UDPSocket();
    ~UDPSocket();
    bool create();
    bool bind(unsigned int port);
    int sendTo(char* buffer, size_t buffer_size, const std::string& ip, unsigned int port);
    int receiveFrom(char* buffer, size_t buffer_size, std::string& sender_ip, unsigned int& sender_port);
    void close();
};

#endif // UDP_SOCKET_HPP_
