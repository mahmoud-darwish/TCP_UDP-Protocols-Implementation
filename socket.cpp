#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "ChannelSocket.hpp"

void TCPSocket::connect(){
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
}
void TCPSocket::shutdown(){
    close(sock);
}
void TCPSocket::send(const std::string& message){
    
    ::send(messageSock, message.c_str(), message.length(), 0);
}
void TCPSocket::receive(){
    std::string buffer(1024, '\0'); 
    int bytes_received = recv(messageSock, &buffer[0], buffer.size(), 0);  // Receive data from client
    if (bytes_received > 0) {
        buffer.resize(bytes_received);  // Resize the string to the number of bytes received
        recievedMessage = buffer;
    } else {
        perror("recv failed");
        //close(new_socket); How will i close this
        //close(server_fd);
        //return -1;
    }
    
}

void UDPSocket::connect(){
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
}
void UDPSocket::shutdown(){
    close(sock);
}
void UDPSocket::send(const std::string& message){
    
    if (sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&UDPdest, (socklen_t )sizeof(UDPdest) ) < 0) {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }
}
void UDPSocket::receive(){
    std::string buffer(1024, '\0');  // Pre-allocate buffer space in the string
    int len = recvfrom(sock, &buffer[0], buffer.size(), 0, 
                       (struct sockaddr*)&UDPdest, (socklen_t *)sizeof(UDPdest));
    if (len > 0) {
        buffer.resize(len);  // Resize string to actual received data size

    }
    
}

