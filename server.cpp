#include "channel.hpp"
#include <iostream>
int main(){
ServerChannel server(1,1000);
server.start();
server.receive();
server.stop();
}
