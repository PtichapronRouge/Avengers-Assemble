CC = g++ -g -std=c++17
ASS = nasm -felf64
CTEST = cxxtestgen --error-printer

BUILD_DIR = build
RUNNER_DIR = $(BUILD_DIR)/runners
SRC_DIR = src
ASM_DIRS = lvl1

TEST_NAME = $(BUILD_DIR)/blas_test.bin
BENCH_NAME = $(BUILD_DIR)/benchmark.bin

UNIT_TESTS = $(ASM_DIRS)/xaxpy_test.hpp
SRC_RUNNER = $(RUNNER_DIR)/runner.cpp

SRC_A = $(wildcard $(ASM_DIRS)/*.asm)
OBJ_A = $(patsubst $(ASM_DIRS)/%.asm, $(BUILD_DIR)/%.o, $(SRC_A))

.PHONY: all clean clearexec setup fresh
all: test

test: $(OBJ_A) $(SRC_RUNNER)
	$(CC) -o $(TEST_NAME) $(SRC_RUNNER) $(OBJ_A)

$(SRC_RUNNER):
	$(CTEST) -o $(SRC_RUNNER) $(UNIT_TESTS)

$(BUILD_DIR)/%.o: $(ASM_DIRS)/%.asm
	$(ASS) $< -o $@

clearexec:
	rm -f $(SRC_RUNNER) $(TEST_NAME)

clean:
	rm -f $(OBJ_A) 

fresh: clean clearexec all

setup:
	mkdir -p $(RUNNER_DIR)

