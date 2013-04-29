cc = g++
CFLAGS = -Wall -o
SRC = main.cpp
EXE = tema1

all:
	$(cc) $(CFLAGS) $(EXE) $(SRC)
clean:
	rm $(EXE)
