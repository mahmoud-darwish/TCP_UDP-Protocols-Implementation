# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Source files
SRCS = ChannelSocket.cpp channel.cpp

# Header files
HEADERS = ChannelSocket.hpp channel.hpp

# Output binaries
CLIENT_TARGET = client_program
SERVER_TARGET = server_program

# Default rule to build both client and server
all: $(CLIENT_TARGET) $(SERVER_TARGET)

# Rule to build the client binary
$(CLIENT_TARGET): client.o $(SRCS:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_TARGET) client.o $(SRCS:.cpp=.o)

# Rule to build the server binary
$(SERVER_TARGET): server.o $(SRCS:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $(SERVER_TARGET) server.o $(SRCS:.cpp=.o)

# Object file compilation rules
client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp

server.o: server.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp

ChannelSocket.o: ChannelSocket.cpp ChannelSocket.hpp
	$(CXX) $(CXXFLAGS) -c ChannelSocket.cpp

channel.o: channel.cpp channel.hpp
	$(CXX) $(CXXFLAGS) -c channel.cpp

# Clean rule to remove object files and binaries
clean:
	rm -f *.o $(CLIENT_TARGET) $(SERVER_TARGET)
