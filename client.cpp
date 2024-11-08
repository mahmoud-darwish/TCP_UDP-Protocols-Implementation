#include "channel.hpp"
#include <iostream>
/*int main(){
ClientChannel client(1,3500);
client.start();
string message = "hello from client";
client.send(message);
client.receive();
cout<< client.get_recievedMessage()<<endl;
client.stop();
}*/
int main(){
ClientChannel client(0,12345);
client.start();
client.receive();
cout<< client.get_recievedMessage()<<endl;
client.stop();
}
