#include <iostream>
#include "ChannelSocket.hpp"
#include "channel.hpp"
//...............................................ServerChannel...........................................................

void ServerChannel::start(){
    int addrlen = sizeof(address);
    channelSocket->connect();
    if(isTCP){
            int option_value=1;
            int status=setsockopt(channelSocket->get_sock(), SOL_SOCKET,SO_REUSEADDR , 
                                &option_value,sizeof(option_value));  
            // check if options are set successfully
            if(status<0){
                perror("Couldn't set options");
                exit(EXIT_FAILURE);
            }
            // Configure the server address
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = htonl(INADDR_ANY);
            address.sin_port = htons(port);
            // Bind the socket to the specified address and port
            if (bind(channelSocket->get_sock(), (struct sockaddr *)&address, sizeof(address)) < 0) {
                perror("Bind failed");
                exit(EXIT_FAILURE);
            }
            // Listen for incoming connections
            if (listen(channelSocket->get_sock(), 3) < 0) {
                perror("Listen failed");
                exit(EXIT_FAILURE);
            }
             // Accept a connection from a client
            int messageSock;
            if ((messageSock = accept(channelSocket->get_sock(), (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }
            channelSocket->set_messageSock(messageSock);
    }
    else{
            const char *multicastIP = "239.255.255.250";  // Multicast address
            // Allow multiple sockets to use the same port
            int reuse = 1;
            if (setsockopt(channelSocket->get_sock(), SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0) {
                perror("Setting SO_REUSEADDR error");
                exit(EXIT_FAILURE);
            }

            // Bind to the local address
            memset(&address, 0, sizeof(address));
            address.sin_family = AF_INET;
            address.sin_port = htons(port);
            address.sin_addr.s_addr = INADDR_ANY;
            if (bind(channelSocket->get_sock(), (struct sockaddr*)&address, sizeof(address)) < 0) {
                perror("Bind failed");
                exit(EXIT_FAILURE);
            }
            // Join the multicast group
            multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastIP);
            multicastRequest.imr_interface.s_addr = INADDR_ANY;
            if (setsockopt(channelSocket->get_sock(), IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multicastRequest, sizeof(multicastRequest)) < 0) {
                perror("Multicast join failed");
                exit(EXIT_FAILURE);
            }
    }
}
void ServerChannel::stop(){
    channelSocket->shutdown();
    if (isTCP)
        close(channelSocket->get_messageSock());
    else
        setsockopt(channelSocket->get_sock(), IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&multicastRequest, sizeof(multicastRequest));
}

void ServerChannel::receive(){
    channelSocket->receive();
}

void ServerChannel::send(const std::string& message){
    channelSocket->send(message);
}

ServerChannel::ServerChannel(bool isTCP,int port): channel( isTCP ,port) {
    if(isTCP)
        channelSocket = new TCPSocket();
    else
        channelSocket = new UDPSocket();
}
//...............................................ClientChannel...........................................................
void ClientChannel::start(){
    channelSocket->connect();
    if(isTCP){
            address.sin_family = AF_INET;
            address.sin_port = htons(port);
            address.sin_addr.s_addr = inet_addr("address");
            // Convert address from text to binary
            if (inet_pton(AF_INET, "192.168.64.8", &address.sin_addr) <= 0) {
                std::cout << "Invalid address / Address not supported" << std::endl;
            }

            // Connect to the server
            if (connect(channelSocket->get_sock(), (struct sockaddr *)&address, sizeof(address)) < 0) {
                std::cout << "Connection failed" << std::endl;
        
            }
    }
    else{
            const char *multicastIP = "239.255.255.250"; 
            memset(&address, 0, sizeof(address));
            address.sin_family = AF_INET;
            address.sin_addr.s_addr = inet_addr(multicastIP);
            address.sin_port = htons(port);
    }
        
}

void ClientChannel::stop(){
    channelSocket->shutdown();
}

void ClientChannel::receive(){
    channelSocket->receive();
}

void ClientChannel::send(const std::string& message){
    channelSocket->send(message);
}

ClientChannel::ClientChannel(bool isTCP, int port): channel( isTCP ,port) {
    if(isTCP)
        channelSocket = new TCPSocket();
    else
        channelSocket = new UDPSocket();
}

