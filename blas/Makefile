CC = g++ -g -std=c++17
ASS = nasm -felf64
CTEST = cxxtestgen --error-printer
PARTFLAG = --part
ROOTFLAG = --root

BUILD_DIR = build
RUNNER_DIR = $(BUILD_DIR)/runners
SRC_DIR = src
ASM_DIRS = lvl1

TEST_NAME = $(BUILD_DIR)/blas_test.bin
BENCH_NAME = $(BUILD_DIR)/benchmark.bin

UNIT_TESTS = $(wildcard $(ASM_DIRS)/*_test.hpp)
RUNNER = $(RUNNER_DIR)/runner.cpp

SRC_A = $(wildcard $(ASM_DIRS)/*.asm)
OBJ_A = $(patsubst $(ASM_DIRS)/%.asm, $(BUILD_DIR)/%.o, $(SRC_A))

SRC_C = $(SRC_DIR)/global.cpp
OBJ_C = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_C))

.PHONY: all clean clearexec setup fresh
all: test

test: $(OBJ_A) $(OBJ_C) $(RUNNER) 
	$(CC) -o $(TEST_NAME) $(OBJ_A) $(OBJ_C) $(RUNNER)

$(RUNNER): 
	$(CTEST) -o $@ $(UNIT_TESTS)

$(BUILD_DIR)/%.o: $(ASM_DIRS)/%.asm
	$(ASS) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $<

clearexec:
	rm -f $(ROOT_RUNNER) $(TEST_NAME)

clean:
	rm -f $(OBJ_A) $(OBJ_C)

fresh: clean clearexec all

setup:
	mkdir -p $(RUNNER_DIR)

