# Makefile para calculadora de expresiones
# Compilador
CC = gcc
# Opciones de compilación
CFLAGS = -I./include -Wall -Wextra
# Nombre del ejecutable
TARGET = calc.exe

# Archivos fuente
SRC_DIR = main
SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/stack.c \
            $(SRC_DIR)/utils.c \
            $(SRC_DIR)/parser.c \
            $(SRC_DIR)/list.c \
            $(SRC_DIR)/dlist.c \
            $(SRC_DIR)/file_manager.c \
            $(SRC_DIR)/conversion_infix_postfix.c \
            $(SRC_DIR)/conversion_infix_prefix.c \
            $(SRC_DIR)/conversion_postfix_infix.c \
            $(SRC_DIR)/conversion_postfix_prefix.c \
            $(SRC_DIR)/conversion_prefix_infix.c \
            $(SRC_DIR)/conversion_prefix_postfix.c

# Archivos objeto
OBJ_FILES = $(SRC_FILES:.c=.o)

# Regla por defecto
all: $(TARGET)

# Enlace para crear el ejecutable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ -lm

# Regla para compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	del /Q $(SRC_DIR)\*.o $(TARGET) 2>nul || rm -f $(SRC_DIR)/*.o $(TARGET)

# Ejecutar el programa en modo interactivo
run: $(TARGET)
	./$(TARGET)

# Mostrar ayuda
help: $(TARGET)
	./$(TARGET) -h

# Mostrar versión
version: $(TARGET)
	./$(TARGET) -v

# Mostrar historial
list: $(TARGET)
	./$(TARGET) -l

# Mostrar estadísticas
stats: $(TARGET)
	./$(TARGET) -s

# Limpiar historial
clear-hist: $(TARGET)
	./$(TARGET) -cl

# Ejemplo de conversión directa
example1: $(TARGET)
	./$(TARGET) "A+B" inf-post

example2: $(TARGET)
	./$(TARGET) "A B +" post-inf

example3: $(TARGET)
	./$(TARGET) "+ A B" pre-inf

# Ayuda del Makefile
make-help:
	@echo "Opciones disponibles:"
	@echo "  make all        - Compilar el proyecto"
	@echo "  make clean      - Limpiar archivos compilados"
	@echo "  make run        - Ejecutar modo interactivo"
	@echo "  make help       - Mostrar ayuda del programa"
	@echo "  make version    - Mostrar versión"
	@echo "  make list       - Mostrar historial"
	@echo "  make stats      - Mostrar estadísticas"
	@echo "  make clear-hist - Limpiar historial"
	@echo "  make example1   - Ejemplo: Infija a Postfija"
	@echo "  make example2   - Ejemplo: Postfija a Infija"
	@echo "  make example3   - Ejemplo: Prefija a Infija"
	@echo "  make make-help  - Mostrar esta ayuda"

.PHONY: all clean run help version list stats clear-hist example1 example2 example3 make-help
