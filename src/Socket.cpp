#include "Socket.hpp"

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

#include <iostream>

bool Socket::initialize()
{
    #ifdef _WIN32
        WSADATA WsaData;
        return WSAStartup( MAKEWORD(2, 2), &WsaData) == NO_ERROR;
    #else
        return true;
    #endif
}

void Socket::destroy()
{
    #ifdef _WIN32
        WSACleanup();
    #endif
}

Socket::~Socket()
{
    if(m_open) close();
}

bool Socket::open(unsigned short port)
{
    m_handle = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );

    if(m_handle <= 0){
        std::cout << "Failed to open socket!" << std::endl;
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(bind(m_handle, (const sockaddr*) &address, sizeof(address)) < 0){
        std::cout << "Failed to bind socket!" << std::endl;
        return false;
    }

    //set the socket to non-blocking by default
    #ifdef _WIN32 
        DWORD nonBlocking = 1;
        if(ioctlsocket( m_handle, FIONBIO, &nonBlocking) != 0){
            std::cout << "Failed to set non-blocking!" << std::endl;
            return false;
        }
    #else
        int nonBlocking = 1;
        if(fcntl( m_handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1){
            std::cout << "Failed to set non-blocking!" << std::endl;
            return false;
        }
    #endif
    
    m_open = true;
    return true;
}

void Socket::close()
{
    m_open = false;
    #ifdef _WIN32
        closesocket(m_handle);
    #else
        ::close(m_handle);
    #endif
}

bool Socket::send(const Address& destination, void* data, int size)
{
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(destination.getAddress());
    address.sin_port = htons(destination.getPort());
    int sentBytes = 
        sendto(m_handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(address)); 
    if(sentBytes != size){
        std::cout << "Failed to send packet!" << std::endl;
        return false;
    }

    return true;
}

int Socket::receive(const Address& source, void* data, int size)
{
    #ifdef _WIN32
        typedef int socklen_t;
    #endif

    sockaddr_in from;
    socklen_t fromLength = sizeof(from);
    return recvfrom(m_handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);
}
