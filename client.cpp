#include "channel.hpp"
#include <iostream>
int main(){
ClientChannel client(1,1000);
client.start();
client.send("hello from client");
client.stop();
}
