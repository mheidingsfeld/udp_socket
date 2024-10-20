#ifndef UDP_SOCKET_HPP_
#define UDP_SOCKET_HPP_

#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    typedef int SOCKET;
#endif

/**
 * @brief Startup Windows sockets. Does nothing on UNIX-like systems.
 * @return true if the startup is successful, false otherwise. 
 */
bool udpSocketStartup();


/**
 * @brief Cleanup Windows sockets. Does nothing on UNIX-like systems.
 */
void udpSocketCleanup();


/**
 * @class UDPSocket
 * @brief Represents a UDP socket.
 */
class UDPSocket {
public:
    /**
     * @brief Default constructor
     */
    UDPSocket();
    
    /**
     * @brief Destructor
     */
    ~UDPSocket();

    /**
     * @brief Creates the UDP socket.
     * @return true if the socket is created successfully, false otherwise.
     */
    bool create();

    /**
     * @brief Binds the socket to a specific port.
     * @param port The port to bind the socket to.
     * @return true if the socket is bound successfully, false otherwise.
     */
    bool bind(unsigned int port);

    /**
     * @brief Sends data to a specific IP address and port.
     * @param buffer Pointer to the data buffer.
     * @param buffer_size The size of the data buffer.
     * @param ip The IP address to send the data to.
     * @param port The port to send the data to.
     * @return The number of bytes sent, or -1 if an error occurs.
     */
    int sendTo(const char* buffer, const int buffer_size, const std::string& ip, unsigned int port);

    /**
     * @brief Receives data from a sender.
     * @param buffer Pointer to the buffer to store the received data.
     * @param buffer_size The size of the buffer.
     * @param sender_ip The IP address of the sender.
     * @param sender_port The port of the sender.
     * @return The number of bytes received, or -1 if an error occurs.
     */
    int receiveFrom(char* buffer, int buffer_size, std::string& sender_ip, unsigned int& sender_port);

    /**
     * @brief Closes the socket
     */
    void close();
private:
    SOCKET sockfd_; /**< The socket file descriptor. */
};

#endif // UDP_SOCKET_HPP_
