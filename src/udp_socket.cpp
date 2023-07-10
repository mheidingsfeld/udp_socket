#include "udp_socket/udp_socket.hpp"

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif


class UDPSocket {
public:
    UDPSocket() : sockfd_(INVALID_SOCKET) {}
    ~UDPSocket() { close(); }

    bool create() {
        sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
        return (sockfd_ != INVALID_SOCKET);
    }

    bool bind(unsigned int port) {
        SOCKADDR_IN server_addr = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(port)
        };

        return (::bind(sockfd_, reinterpret_cast<SOCKADDR*>(&server_addr), sizeof(server_addr)) != SOCKET_ERROR);
    }

    ssize_t sendTo(char* buffer, size_t buffer_size, const std::string& ip, unsigned int port) {
        SOCKADDR_IN dest_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(port)
        };
        if (inet_pton(AF_INET, ip.c_str(), &(dest_addr.sin_addr)) <= 0) {
            return -1;
        }

        return sendto(sockfd_, buffer, buffer_size, 0,
                      reinterpret_cast<SOCKADDR*>(&dest_addr), sizeof(dest_addr));
    }

    ssize_t receiveFrom(char* buffer, size_t buffer_size, std::string& sender_ip, unsigned int& sender_port) {
        SOCKADDR_IN sender_addr;
        socklen_t sender_addr_len = sizeof(sender_addr);

        ssize_t recv_bytes = recvfrom(sockfd_, buffer, buffer_size - 1, 0,
                                     reinterpret_cast<SOCKADDR*>(&sender_addr), &sender_addr_len);
        if (recv_bytes >= 0) {
            buffer[recv_bytes] = '\0';
            sender_ip = inet_ntoa(sender_addr.sin_addr);
            sender_port = ntohs(sender_addr.sin_port);
        }
        return recv_bytes;
    }

    void close() {
        if (sockfd_ != INVALID_SOCKET) {
#ifdef _WIN32
            closesocket(sockfd_);
#else
            ::close(sockfd_);
#endif
            sockfd_ = INVALID_SOCKET;
        }
    }

private:
    SOCKET sockfd_;
};
