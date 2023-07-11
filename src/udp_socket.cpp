#include "udp_socket/udp_socket.hpp"

#ifdef _WIN32
    #include <WS2tcpip.h>
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif


UDPSocket::UDPSocket() : sockfd_(INVALID_SOCKET) {}

UDPSocket::~UDPSocket() { close(); }

bool UDPSocket::create() {
    sockfd_ = socket(AF_INET, SOCK_DGRAM, 0);
    return (sockfd_ != INVALID_SOCKET);
}

bool UDPSocket::bind(unsigned int port) {
    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    return (::bind(sockfd_, reinterpret_cast<SOCKADDR*>(&server_addr), sizeof(server_addr)) != SOCKET_ERROR);
}

int UDPSocket::sendTo(const char* buffer, const int buffer_size, const std::string& ip, unsigned int port) {
    SOCKADDR_IN dest_addr = {};
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &(dest_addr.sin_addr)) <= 0) {
        return -1;
    }

    return sendto(sockfd_, buffer, buffer_size, 0,
                    reinterpret_cast<SOCKADDR*>(&dest_addr), sizeof(dest_addr));
}

int UDPSocket::receiveFrom(char* buffer, int buffer_size, std::string& sender_ip, unsigned int& sender_port) {
    SOCKADDR_IN sender_addr = {};
    socklen_t sender_addr_len = sizeof(sender_addr);

    int recv_bytes = recvfrom(sockfd_, buffer, buffer_size - 1, 0,
                                    reinterpret_cast<SOCKADDR*>(&sender_addr), &sender_addr_len);
    if (recv_bytes >= 0) {
        buffer[recv_bytes] = '\0';
        char ipBuffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sender_addr.sin_addr), ipBuffer, INET_ADDRSTRLEN);
        sender_ip = ipBuffer;
        sender_port = ntohs(sender_addr.sin_port);
        //sender_ip = inet_ntoa(sender_addr.sin_addr);
        //sender_port = ntohs(sender_addr.sin_port);
    }
    return recv_bytes;
}

void UDPSocket::close() {
    if (sockfd_ != INVALID_SOCKET) {
#ifdef _WIN32
        closesocket(sockfd_);
#else
        ::close(sockfd_);
#endif
        sockfd_ = INVALID_SOCKET;
    }
}
