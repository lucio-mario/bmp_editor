# Directories
BUILD_DIR = build
BIN_DIR = $(BUILD_DIR)/bin
OBJ_DIR = $(BUILD_DIR)/obj
SRC_DIR = src

# Toolchain
CC = gcc
RM = rm

# Files
TARGET = $(BIN_DIR)/bmp_editor
SOURCES = $(wildcard $(SRC_DIR)/*.c)
SOURCE_NAMES = $(patsubst $(SRC_DIR)/%,%,$(SOURCES))
OBJECT_NAMES = $(SOURCE_NAMES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Flags
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = $(WFLAGS) -Os
LFLAGS = # Linking flags

# Build
## Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $^ -o $@

## Compiling
#	This doesn't account for changes in $(SRC_DIR)/%.h as a prerequisite, and it can't be simply \
	inserted into the prerequisites below because there are %.c files that doesn't have a %.h \
	correspondent like main.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/common.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Phonies
.PHONY: all clean run print

all: $(TARGET)

clean:
	@$(RM) -r $(BUILD_DIR)

run:
	./$(TARGET)

print:
	@echo sources: $(SOURCES)
	@echo source_names: $(SOURCE_NAMES)
	@echo objects: $(OBJECTS)
	@echo objec_names: $(OBJECT_NAMES)
