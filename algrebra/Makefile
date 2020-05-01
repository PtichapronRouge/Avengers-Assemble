CC = g++
ASS = nasm -felf64
CTEST = cxxtestgen --error-printer

#EXEC_NAME = test
TEST_NAME = algebra_runner

UNIT_TESTS = algebra_test.hpp
#SRC_C = tests.cpp
#OBJ_C = $(SRC_C:.cpp=.o)

SRC_RUNNER = runner.cpp
SRC_A = scalar.asm norm.asm matrix_product.asm
OBJ_A = $(SRC_A:.asm=.o)

test: $(OBJ_A) $(SRC_RUNNER)
	$(CC) -o $(TEST_NAME) $(SRC_RUNNER) $(OBJ_A)

$(SRC_RUNNER): 
	$(CTEST) -o $(SRC_RUNNER) $(UNIT_TESTS)

$(OBJ_A): %.o: %.asm
	$(ASS) $< -o $@

#test: $(OBJ_C) $(OBJ_A)
	#g++ -o $(EXEC_NAME) $(OBJ_C) $(OBJ_A)

#$(OBJ_C): $(SRC_C)

.PHONY: clean
clean:
	rm -f $(OBJ_A) $(SRC_RUNNER) $(TEST_NAME)

