# Makefile for running two programs

# Choose the compiler.
CC = g++ -std=c++11 -pthread
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES := server/Knn.o
BUILD_FILES += server/DistanceFactory.o
BUILD_FILES += server/distances.o 
BUILD_FILES += server/select.o
BUILD_FILES += server/IDistance.o
BUILD_FILES += server/ServerClass.o
BUILD_FILES += client/ClientClass.o
BUILD_FILES += server/Cli.o 
BUILD_FILES += client/CliClient.o
BUILD_FILES += server/Command.o
BUILD_FILES += server/AlgorithmSettingCommand.o
BUILD_FILES += server/ManageData.o
BUILD_FILES += server/SocketIO.o
BUILD_FILES += client/CommandClient.o
BUILD_FILES += client/SocketIOCli.o
BUILD_FILES += server/UploadCommand.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: server/server.cpp
	$(CC) -c -o server.o server/server.cpp
client.o: client/client.cpp
	$(CC) -c -o client.o client/client.cpp


# Clean command
clean:
	$(CLN) server/*.o client/*.o server.out client.out