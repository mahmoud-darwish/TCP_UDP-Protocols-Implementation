#include <iostream>
using namespace std;
class socket{
    virtual void connect() = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
    virtual void shutdown() = 0;
};
