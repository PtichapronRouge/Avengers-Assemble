CC = g++ -g -std=c++17
CTEST = cxxtestgen --error-printer
PARTFLAG = --part
ROOTFLAG = --root

BUILD_DIR = build
export BUILD_DIR

RUNNER_DIR = $(BUILD_DIR)/runners
SRC_DIR = src
TEST_DIR = tests

TEST_NAME = $(BUILD_DIR)/blas_test.bin
BENCH_NAME = $(BUILD_DIR)/benchmark.bin

UNIT_TESTS = $(wildcard $(TEST_DIR)/*_test.hpp)
RUNNER = $(RUNNER_DIR)/runner.cpp

# To fucking improve, it's ugly af
OBJ_A1 = $(patsubst lvl1/%.asm,$(BUILD_DIR)/%.o, $(wildcard lvl1/*.asm))
OBJ_A2 = $(patsubst lvl2/%.asm,$(BUILD_DIR)/%.o, $(wildcard lvl2/*.asm))
OBJ_A3 = $(patsubst lvl3/%.asm,$(BUILD_DIR)/%.o, $(wildcard lvl3/*.asm))
OBJ_A = $(OBJ_A1) $(OBJ_A2) $(OBJ_A3)

SRC_C = $(SRC_DIR)/global.cpp
OBJ_C = $(SRC_C:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

.PHONY: all clean clearexec setup fresh disp
disp: 
	echo $(OBJ_A)

all: test

test: blas unit_tests

blas:
	$(MAKE) -C lvl1
	$(MAKE) -C lvl2
	#$(MAKE) -C lvl3

unit_tests: $(OBJ_A) $(OBJ_C) $(RUNNER) 
	$(CC) -o $(TEST_NAME) $(OBJ_A) $(OBJ_C) $(RUNNER)

$(RUNNER): 
	$(CTEST) -o $@ $(UNIT_TESTS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $<

clearexec:
	rm -f $(ROOT_RUNNER) $(TEST_NAME)

clean:
	rm -f $(OBJ_A) $(OBJ_C)

fresh: clean clearexec all

setup:
	mkdir -p $(RUNNER_DIR)

