ASS = nasm -felf64
ifdef BUILD_DIR
	BUILD_DIR := ../$(BUILD_DIR)
else
	BUILD_DIR := .
endif

ASM = $(wildcard *.asm)
OBJ = $(ASM:%.asm=$(BUILD_DIR)/%.o)

.PHONY: all clean
all: $(OBJ)

$(BUILD_DIR)/%.o:%.asm
	$(ASS) $< -o $@

clean:
	rm -f $(OBJ)
