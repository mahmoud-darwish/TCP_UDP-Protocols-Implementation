#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
class ChannelSocket{
    protected:
        int sock;
        int messageSock;
        std::string recievedMessage;
        struct sockaddr_in UDPdest;
    public:
        virtual void connect() = 0;
        virtual void send(const std::string& message) = 0;
        virtual void receive() = 0;
        virtual void shutdown() = 0;
};
class TCPSocket:ChannelSocket{
    virtual void connect() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
    virtual void shutdown() override;
};
class UDPSocket:ChannelSocket{
    virtual void connect() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
    virtual void shutdown() override;
};
