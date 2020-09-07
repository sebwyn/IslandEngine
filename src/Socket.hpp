#pragma once

class Address {
public:
    Address() = default;
    Address(char a, char b, char c, char d, unsigned short port)
     : port(port)
    {
        address = (a << 24) | (b << 16) | (c << 8) | d;
    }
    Address(unsigned int address, unsigned short port)
     : address(address), port(port)
    {}

    unsigned int getAddress() const { return address; }
    unsigned short getPort() const { return port; }

    unsigned char getA() const { return (address >> 24); }
    unsigned char getB() const { return (address >> 16); }
    unsigned char getC() const { return (address >>  8); }
    unsigned char getD() const { return address; }
private:
    unsigned int address;
    unsigned short port;
};

/*
 * a barebones cross-platform udp socket 
 *
 */
class Socket {
public:
    static bool initialize();
    static void destroy();

    ~Socket(); 

    bool open(unsigned short port);

    void close();

    bool isOpen() const { return m_open; }

    bool send(const Address& destination, void* data, int size);
    int receive(const Address& source, void* data, int size);

private:
    bool m_open;
    int m_handle;
};
