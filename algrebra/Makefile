CC = g++ -g
ASS = nasm -felf64
CTEST = cxxtestgen --error-printer

BUILDIR = build
SOURCEDIR = src

TEST_NAME = $(BUILDIR)/algebra_runner.bin
BENCH_NAME = $(BUILDIR)/benchmark.bin

UNIT_TESTS = $(SOURCEDIR)/algebra_test.hpp
SRC_RUNNER = $(SOURCEDIR)/runner.cpp

SRC_A = $(wildcard $(SOURCEDIR)/*.asm)
OBJ_A = $(patsubst $(SOURCEDIR)/%.asm, $(BUILDIR)/%.o, $(SRC_A))

test: $(OBJ_A) $(SRC_RUNNER)
	$(CC) -o $(TEST_NAME) $(SRC_RUNNER) $(OBJ_A)

$(SRC_RUNNER): 
	$(CTEST) -o $(SRC_RUNNER) $(UNIT_TESTS)

$(BUILDIR)/%.o: $(SOURCEDIR)/%.asm
	$(ASS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_A) $(SRC_RUNNER) $(TEST_NAME)

