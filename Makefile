#set up the compiler and necessary compilation flags.
CC = g++ -std=c++11

OBJS = DistanceFactory.o distances.o Knn.o select.o IDistance.o GetInput.o Server.o

ifeq ($(OS),Windows_NT)
	RM = del /F /Q
	EXE = a.exe
else
	RM = rm -rf
	ERROR_IGNORE = 2>/dev/null
	EXE = a.out
endif

#linking command
all: $(OBJS) server_main.o
	$(CC) $(OBJS) server_main.o

%.o: %.cpp %.hpp
	$(CC) -c $< -o $@

server.o: server_main.cpp
	$(CC) -c server_main.cpp

clean:
	$(RM) $(OBJS) $(ERROR_IGNORE)
	$(RM) $(EXE) $(ERROR_IGNORE)
