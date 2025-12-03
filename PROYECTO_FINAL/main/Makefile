# ========================================================================================================================
# Makefile para Calculadora de Expresiones
# ========================================================================================================================

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2 -I../include
LDFLAGS = -lm
TARGET = calc

# Directorios
SRC_DIR = .
INC_DIR = ../include
BUILD_DIR = build

# ========================================================================================================================
# ARCHIVOS DEL PROYECTO 
# ========================================================================================================================

# Archivos principales
MAIN_SOURCES = main.c
MAIN_OBJECTS = $(BUILD_DIR)/main.o

# Módulos de estructuras de datos
DATA_STRUCT_SOURCES = stack.c dlist.c
DATA_STRUCT_OBJECTS = $(BUILD_DIR)/stack.o $(BUILD_DIR)/dlist.o
DATA_STRUCT_HEADERS = $(INC_DIR)/stack.h $(INC_DIR)/dlist.h

# Módulos de conversión
CONVERSION_SOURCES = \
    conversion_infix_postfix.c \
    conversion_infix_prefix.c \
    conversion_postfix_infix.c \
    conversion_postfix_prefix.c \
    conversion_prefix_infix.c \
    conversion_prefix_postfix.c

CONVERSION_OBJECTS = $(BUILD_DIR)/conversion_infix_postfix.o \
                     $(BUILD_DIR)/conversion_infix_prefix.o \
                     $(BUILD_DIR)/conversion_postfix_infix.o \
                     $(BUILD_DIR)/conversion_postfix_prefix.o \
                     $(BUILD_DIR)/conversion_prefix_infix.o \
                     $(BUILD_DIR)/conversion_prefix_postfix.o

# Módulos de utilidades
UTILS_SOURCES = utils.c parser.c file_manager.c
UTILS_OBJECTS = $(BUILD_DIR)/utils.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/file_manager.o

# Agrupar todos los archivos
ALL_SOURCES = $(MAIN_SOURCES) $(DATA_STRUCT_SOURCES) $(CONVERSION_SOURCES) $(UTILS_SOURCES)
ALL_OBJECTS = $(MAIN_OBJECTS) $(DATA_STRUCT_OBJECTS) $(CONVERSION_OBJECTS) $(UTILS_OBJECTS)

# ========================================================================================================================
# REGLAS DE COMPILACIÓN
# ========================================================================================================================

# Crear directorio de build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regla principal
all: $(BUILD_DIR) $(TARGET)

# Compilación del ejecutable final
$(TARGET): $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(ALL_OBJECTS) $(LDFLAGS)
	@echo "=================================================="
	@echo " Compilación exitosa!"
	@echo "   Ejecutable: ./$(TARGET)"
	@echo "=================================================="

# Regla genérica para compilar .c a .o
$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ========================================================================================================================
# REGLAS DE EJECUCIÓN
# ========================================================================================================================

run: $(TARGET)
	./$(TARGET)

help: $(TARGET)
	./$(TARGET) -h

# ========================================================================================================================
# REGLAS DE MANTENIMIENTO
# ========================================================================================================================

clean:
	rm -f $(TARGET) $(ALL_OBJECTS)
	rm -rf $(BUILD_DIR)
	@echo " Archivos de compilación eliminados"

distclean: clean
	rm -f operaciones.txt historial.log debug.log
	rm -f *.out *.exe core vgcore.*
	@echo " Limpieza profunda completada"

# ========================================================================================================================
# REGLAS DE INFORMACIÓN
# ========================================================================================================================

info:
	@echo "=================================================="
	@echo " CALCULADORA DE EXPRESIONES MATEMÁTICAS"
	@echo "=================================================="
	@echo "Target: $(TARGET)"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Directorio fuente: $(SRC_DIR)"
	@echo "Directorio include: $(INC_DIR)"
	@echo "Directorio build: $(BUILD_DIR)"
	@echo "=================================================="

.PHONY: all clean distclean run help info
