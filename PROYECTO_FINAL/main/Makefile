CC = gcc
CFLAGS = -Wall -Wextra -I./Include
TARGET = calculadora
SRC_DIR = Main
OBJ_DIR = Obj

# Lista de archivos fuente
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/conversion_infix_prefix.c \
       $(SRC_DIR)/conversion_infix_postfix.c \
       $(SRC_DIR)/conversion_prefix_infix.c \
       $(SRC_DIR)/conversion_prefix_postfix.c \
       $(SRC_DIR)/conversion_postfix_infix.c \
       $(SRC_DIR)/conversion_postfix_prefix.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/stack.c \
       $(SRC_DIR)/utils.c \
       $(SRC_DIR)/dlist.c \
       $(SRC_DIR)/list.c \
       $(SRC_DIR)/file_manager.c

# Archivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
