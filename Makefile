# Makefile for running two programs

# Choose the compiler.
CC = g++ -std=c++11
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES := Knn.o
BUILD_FILES += DistanceFactory.o
BUILD_FILES += distances.o 
BUILD_FILES += select.o
BUILD_FILES += IDistance.o
BUILD_FILES += Server.o
BUILD_FILES += Client.o
BUILD_FILES += GetInput.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out
	$(CC) $(BUILD_FILES) client.o -o client.out

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: Server.cpp
	$(CC) -c -o server.o server.cpp
client.o: Client.cpp
	$(CC) -c -o client.o client.cpp


# Clean command
clean:
	$(CLN) *.o server.out client.out