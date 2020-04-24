CC = g++
ASS = nasm -felf64

EXEC_NAME = test

SRC_C = tests.cpp
OBJ_C = $(SRC_C:.cpp=.o)

SRC_A = scalar.asm norm.asm
OBJ_A = $(SRC_A:.asm=.o)

test: $(OBJ_C) $(OBJ_A)
	g++ -o $(EXEC_NAME) $(OBJ_C) $(OBJ_A)

$(OBJ_C): $(SRC_C)

$(OBJ_A): %.o: %.asm
	$(ASS) $< -o $@

.PHONY: clean
clean:
	rm test $(OBJ_C) $(OBJ_A)

