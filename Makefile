CC=g++
CFLAGS=-Wall -Wextra -g -std=c++17
EXE=sivsdl
OBJ=main.o
LIBS=-lSDL2 -lSDL2_image


.PHONY: all

all: $(EXE)

clean:
	rm $(EXE) $(OBJ)

run: $(EXE)
	./$(EXE) test.png

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@

main.o: main.cpp
	$(CC) -c $(CFLAGS) $? -o $@