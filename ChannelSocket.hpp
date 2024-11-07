#ifndef CHANNELSOCKET_HPP
#define CHANNELSOCKET_HPP
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
    public:
        struct sockaddr_in UDPdest;
        int get_sock();
        int get_messageSock();
        void set_messageSock(int messageSock);
        string get_recievedMessage();
        virtual void connect() = 0;
        virtual void send(const std::string& message) = 0;
        virtual void receive() = 0;
        virtual void shutdown() = 0;
        virtual ~ChannelSocket() {}
        
};
class TCPSocket:public ChannelSocket{
    virtual void connect() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
    virtual void shutdown() override;
};
class UDPSocket:public ChannelSocket{
    virtual void connect() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
    virtual void shutdown() override;
};
#endif  
