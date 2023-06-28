# Project
TARGET = string_functions_test

# Toolchain definitions
CC = gcc

# C flags
CFLAGS += -Wall
CFLAGS += -O3
CFLAGS += -std=c11

# Linker flags
LFLAGS += -Wall
LFLAGS += -O3
LFLAGS += -std=c11


C_SRC += $(shell find ./src -name '*.c')
OBJS += $(C_SRC:.c=.o)

INCLUDE = -I"./inc"
SYMBOLS = -DTEST




.PHONY: all
all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $(SYMBOLS) $(INCLUDE) $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(LFLAGS) -o $@


.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)







