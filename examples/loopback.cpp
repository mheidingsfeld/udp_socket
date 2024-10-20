#include <udp_socket/udp_socket.hpp>

#include <iostream>
#include <csignal>
#include <chrono>
#include <thread>


#define RECV_PORT 8888


void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received. Stopping." << std::endl;
    exit(signum);
}


int main() {
    if(!udpSocketStartup()) {
        std::cerr << "Failed to initialize winsock." << std::endl;
        return 1;        
    }

    // Register signal handler
    signal(SIGINT, signalHandler);

    // Create send socket
    UDPSocket send_socket;
    if (!send_socket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    // Create & bind to receive socket
    UDPSocket recv_socket;
    if (!recv_socket.create()) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }
    if (!recv_socket.bind(RECV_PORT)) {
        std::cerr << "Failed to bind socket." << std::endl;
        return 1;
    }

    char buffer[1024];
    std::string sender_ip;
    unsigned int sender_port;

    std::cout << "Waiting for messages on port " << RECV_PORT << " ..." << std::endl;
    while (1) {
        int recv_bytes = 0;

        while ((recv_bytes = recv_socket.receiveFrom(buffer, sizeof(buffer), sender_ip, sender_port)) > 0) {
            std::cout << "Received message from " << sender_ip << ":" << sender_port << ": " << buffer << std::endl;
            if (send_socket.sendTo(buffer, recv_bytes, sender_ip, sender_port) < 0) {
                std::cerr << "Failed to send message." << std::endl;
                return 1;
            }
        }

        if (recv_bytes < 0) {
            std::cerr << "Failed to receive message." << std::endl;
            return 1;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    udpSocketCleanup();

    return 0;
}
