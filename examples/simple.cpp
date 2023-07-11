#include "udp_socket/udp_socket.hpp"

#include <iostream>


#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888


int main() {
    if(!udpSocketStartup()) {
        std::cerr << "Failed to initialize winsock." << std::endl;
        return 1;        
    }

    UDPSocket client_socket;
    if (!client_socket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    UDPSocket server_socket;
    if (!server_socket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    if (!server_socket.bind(SERVER_PORT)) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    if (client_socket.sendTo(message.c_str(), static_cast<const int>(message.size()), SERVER_IP, SERVER_PORT) < 0) {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    char buffer[1024];
    std::string sender_ip;
    unsigned int sender_port;

    int recv_bytes = server_socket.receiveFrom(buffer, sizeof(buffer), sender_ip, sender_port);
    if (recv_bytes < 0) {
        std::cerr << "Failed to receive message." << std::endl;
        return 1;
    }

    std::cout << "Received message from " << sender_ip << ":" << sender_port << ": " << buffer << std::endl;

    udpSocketCleanup();

    return 0;
}
