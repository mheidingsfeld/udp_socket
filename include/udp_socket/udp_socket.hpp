#ifndef UDP_SOCKET_HPP_
#define UDP_SOCKET_HPP_

#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    typedef int SOCKET;
#endif

class UDPSocket {
public:
    UDPSocket();
    ~UDPSocket();
    bool create();
    bool bind(unsigned int port);
    int sendTo(const char* buffer, const int buffer_size, const std::string& ip, unsigned int port);
    int receiveFrom(char* buffer, int buffer_size, std::string& sender_ip, unsigned int& sender_port);
    void close();
private:
    SOCKET sockfd_;
};

#endif // UDP_SOCKET_HPP_
