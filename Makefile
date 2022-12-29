#set up the compiler and necessary compilation flags.
CC = g++ -std=c++11

OBJS = DistanceFactory.o distances.o Knn.o select.o IDistance.o

ifeq ($(OS),Windows_NT)
	RM = del /F /Q
	EXE = a.exe
else
	RM = rm -rf
	ERROR_IGNORE = 2>/dev/null
	EXE = a.out
endif

#linking command
all: $(OBJS) getVector.o
	$(CC) $(OBJS) getVector.o

%.o: %.cpp %.hpp
	$(CC) -c $< -o $@

getVector.o: getVector.cpp
	$(CC) -c getVector.cpp

clean:
	$(RM) $(OBJS) $(ERROR_IGNORE)
	$(RM) $(EXE) $(ERROR_IGNORE)
