#include "channel.hpp"
#include <iostream>
int main(){
ServerChannel server(1,3500);
server.start();
server.receive();
cout<< server.get_recievedMessage()<<endl;
string message = "hello from server";
server.send(message);
server.stop();
}
