#include "channel.hpp"
#include <iostream>
/*int main(){
ClientChannel client(TCP,3500);
client.start();
string message = "hello from client";
client.send(message);
client.receive();
cout<< client.get_recievedMessage()<<endl;
client.stop();
}*/
int main(){
ClientChannel client(UDP,12345);
client.start();
client.receive();
cout<< client.get_recievedMessage()<<endl;
client.stop();
}
