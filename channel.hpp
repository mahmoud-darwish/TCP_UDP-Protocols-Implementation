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