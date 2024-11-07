#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <iostream>
#include "ChannelSocket.hpp"
using namespace std;
class channel{
    protected:
        ChannelSocket* channelSocket;
        bool isTCP;
        struct sockaddr_in address;
        int port;
    public:
        string get_recievedMessage();
        channel(bool isTCP,int port) : port(port), isTCP(isTCP) {}
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void send(const std::string& message) = 0;
        virtual void receive() = 0;
        virtual ~channel() {
        if (channelSocket != nullptr) {
            delete channelSocket;
        }
    }
    };
class ServerChannel:public channel{
    private:
        struct ip_mreq multicastRequest;
    public:
        ServerChannel(bool isTCP, int port);
        virtual void start() override;
        virtual void stop() override;
        virtual void send(const std::string& message) override;
        virtual void receive() override;
};
class  ClientChannel:public channel{
    public:
        ClientChannel(bool isTCP, int port);
        virtual void start() override;
        virtual void stop() override;
        virtual void send(const std::string& message) override;
        virtual void receive() override;
};
#endif  