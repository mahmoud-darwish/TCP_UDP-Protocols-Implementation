#include "channel.hpp"
#include <iostream>
/*int main(){
ServerChannel server(TCP,3500);
server.start();
server.receive();
cout<< server.get_recievedMessage()<<endl;
string message = "hello from server";
server.send(message);
server.stop();
}*/
int main(){
ServerChannel server(UDP,12345);
server.start();
string message = "hello from server";
server.send(message);
server.stop();
}
