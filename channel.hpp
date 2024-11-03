#include <iostream>
#include "socket.hpp"
using namespace std;
class channel{
    socket* channelSocket;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
};
class ServerChannel:channel{
 virtual void start() override;
    virtual void stop() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
};
class  ClientChannel:channel{
 virtual void start() override;
    virtual void stop() override;
    virtual void send(const std::string& message) override;
    virtual void receive() override;
};