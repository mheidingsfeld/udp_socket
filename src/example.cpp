#include "udp_socket/udp_socket.hpp"

#include <iostream>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888


int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize winsock." << std::endl;
        return 1;
    }
#endif

    UDPSocket clientSocket;
    if (!clientSocket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    UDPSocket serverSocket;
    if (!serverSocket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    if (!serverSocket.bind(SERVER_PORT)) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    if (clientSocket.sendTo(message.c_str(), message.size(), SERVER_IP, SERVER_PORT) < 0) {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    char buffer[1024];
    std::string sender_ip;
    unsigned int sender_port;

    ssize_t recvBytes = serverSocket.receiveFrom(buffer, sizeof(buffer), sender_ip, sender_port);
    if (recvBytes < 0) {
        std::cerr << "Failed to receive message." << std::endl;
        return 1;
    }

    std::cout << "Received message from " << sender_ip << ":" << sender_port << ": " << buffer << std::endl;

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}