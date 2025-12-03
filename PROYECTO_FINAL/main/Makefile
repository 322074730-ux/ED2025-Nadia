# ========================================================================================================================
# Makefile para Calculadora de Expresiones
# ========================================================================================================================

# Compilador y flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
LDFLAGS = -lm
TARGET = calc

# ========================================================================================================================
# ARCHIVOS DEL PROYECTO 
# ========================================================================================================================

# Archivos principales
MAIN_SOURCES = main.c
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)

# Módulos de estructuras de datos
DATA_STRUCT_SOURCES = stack.c dlist.c
DATA_STRUCT_OBJECTS = $(DATA_STRUCT_SOURCES:.c=.o)
DATA_STRUCT_HEADERS = stack.h dlist.h

# Módulos de conversión
CONVERSION_SOURCES = \
    conversion_infix_postfix.c \
    conversion_infix_prefix.c \
    conversion_postfix_infix.c \
    conversion_postfix_prefix.c \
    conversion_prefix_infix.c \
    conversion_prefix_postfix.c

CONVERSION_OBJECTS = $(CONVERSION_SOURCES:.c=.o)

CONVERSION_HEADERS = \
    conversion_infix_postfix.h \
    conversion_infix_prefix.h \
    conversion_postfix_infix.h \
    conversion_postfix_prefix.h \
    conversion_prefix_infix.h \
    conversion_prefix_postfix.h

# Módulos de utilidades
UTILS_SOURCES = utils.c parser.c file_manager.c
UTILS_OBJECTS = $(UTILS_SOURCES:.c=.o)
UTILS_HEADERS = utils.h parser.h file_manager.h

# Agrupar todos los archivos
ALL_SOURCES = $(MAIN_SOURCES) $(DATA_STRUCT_SOURCES) $(CONVERSION_SOURCES) $(UTILS_SOURCES)
ALL_OBJECTS = $(MAIN_OBJECTS) $(DATA_STRUCT_OBJECTS) $(CONVERSION_OBJECTS) $(UTILS_OBJECTS)
ALL_HEADERS = $(DATA_STRUCT_HEADERS) $(CONVERSION_HEADERS) $(UTILS_HEADERS)

# ========================================================================================================================
# REGLAS DE COMPILACIÓN
# ========================================================================================================================

# Regla principal
all: $(TARGET)

# Compilación del ejecutable final
$(TARGET): $(ALL_OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(ALL_OBJECTS) $(LDFLAGS)
	@echo "=================================================="
	@echo " Compilación exitosa!"
	@echo "   Ejecutable: ./$(TARGET)"
	@echo "   Módulos compilados:"
	@echo "   - Estructuras: $(DATA_STRUCT_SOURCES)"
	@echo "   - Conversiones: $(CONVERSION_SOURCES)"
	@echo "   - Utilidades: $(UTILS_SOURCES)"
	@echo "=================================================="

# ========================================================================================================================
# REGLAS DE COMPILACIÓN POR MÓDULO
# ========================================================================================================================

# Módulo principal
main.o: main.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -c main.c
	@echo " main.c compilado"

# Módulos de estructuras de datos
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
	@echo " stack.c compilado"

dlist.o: dlist.c dlist.h
	$(CC) $(CFLAGS) -c dlist.c
	@echo " dlist.c compilado"

# Módulos de conversión
conversion_infix_postfix.o: conversion_infix_postfix.c conversion_infix_postfix.h
	$(CC) $(CFLAGS) -c conversion_infix_postfix.c
	@echo " conversion_infix_postfix.c compilado"

conversion_infix_prefix.o: conversion_infix_prefix.c conversion_infix_prefix.h
	$(CC) $(CFLAGS) -c conversion_infix_prefix.c
	@echo " conversion_infix_prefix.c compilado"

conversion_postfix_infix.o: conversion_postfix_infix.c conversion_postfix_infix.h
	$(CC) $(CFLAGS) -c conversion_postfix_infix.c
	@echo " conversion_postfix_infix.c compilado"

conversion_postfix_prefix.o: conversion_postfix_prefix.c conversion_postfix_prefix.h
	$(CC) $(CFLAGS) -c conversion_postfix_prefix.c
	@echo " conversion_postfix_prefix.c compilado"

conversion_prefix_infix.o: conversion_prefix_infix.c conversion_prefix_infix.h
	$(CC) $(CFLAGS) -c conversion_prefix_infix.c
	@echo " conversion_prefix_infix.c compilado"

conversion_prefix_postfix.o: conversion_prefix_postfix.c conversion_prefix_postfix.h
	$(CC) $(CFLAGS) -c conversion_prefix_postfix.c
	@echo " conversion_prefix_postfix.c compilado"

# Módulos de utilidades
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c
	@echo " utils.c compilado"

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c
	@echo " parser.c compilado"

file_manager.o: file_manager.c file_manager.h
	$(CC) $(CFLAGS) -c file_manager.c
	@echo " file_manager.c compilado"

# ========================================================================================================================
# REGLAS DE EJECUCIÓN Y PRUEBAS
# ========================================================================================================================

# Ejecutar el programa
run: $(TARGET)
	@echo " Ejecutando calculadora..."
	@echo "=================================================="
	./$(TARGET)

# Mostrar ayuda del programa
help: $(TARGET)
	@echo " Mostrando ayuda de la calculadora..."
	@echo "=================================================="
	./$(TARGET) -h

# Ejecutar pruebas de conversión
test-conversions: $(TARGET)
	@echo " Ejecutando pruebas de conversión..."
	@echo "=================================================="
	@echo "Test 1: Infija -> Postfija"
	@echo "Test 2: Infija -> Prefija"
	@echo "Test 3: Postfija -> Infija"
	@echo "Test 4: Postfija -> Prefija"
	@echo "Test 5: Prefija -> Infija"
	@echo "Test 6: Prefija -> Postfija"
	@echo "=================================================="

# Prueba específica de expresión
test-expr: $(TARGET)
	@echo "Probando expresión: (3+4)*5"
	@echo "=================================================="
	@echo "Ejecuta manualmente y prueba la expresión"

# ========================================================================================================================
# REGLAS DE MANTENIMIENTO
# ========================================================================================================================

# Limpiar archivos compilados
clean:
	rm -f $(TARGET) $(ALL_OBJECTS) *.o
	@echo " Archivos de compilación eliminados"

# Limpieza profunda (incluye archivos de datos)
distclean: clean
	rm -f operaciones.txt historial.log debug.log
	rm -f *.out *.exe core vgcore.*
	@echo " Limpieza profunda completada"

# Compilar en modo depuración
debug: CFLAGS += -DDEBUG -g -O0
debug: clean $(TARGET)
	@echo " Compilado en modo depuración"
	@echo " Flags: -DDEBUG -g -O0"

# Compilar con optimización máxima
release: CFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)
	@echo "Compilado en modo release (optimizado)"

# ========================================================================================================================
# REGLAS DE INFORMACIÓN
# ========================================================================================================================

# Mostrar información del proyecto
info:
	@echo "=================================================="
	@echo " CALCULADORA DE EXPRESIONES MATEMÁTICAS"
	@echo "=================================================="
	@echo "Target: $(TARGET)"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo ""
	@echo "  ARCHIVOS FUENTE:"
	@echo "   Principal: $(MAIN_SOURCES)"
	@echo "   Estructuras: $(DATA_STRUCT_SOURCES)"
	@echo "   Conversión:"
	@for file in $(CONVERSION_SOURCES); do \
		echo "     - $$file"; \
	done
	@echo "   Utilidades: $(UTILS_SOURCES)"
	@echo ""
	@echo "  ARCHIVOS CABECERA:"
	@for file in $(ALL_HEADERS); do \
		echo "     - $$file"; \
	done
	@echo "=================================================="
	@echo "   COMANDOS DISPONIBLES:"
	@echo "   make              - Compilar proyecto completo"
	@echo "   make run          - Compilar y ejecutar"
	@echo "   make help         - Mostrar ayuda del programa"
	@echo "   make test-conversions - Probar conversiones"
	@echo "   make clean        - Limpiar archivos objeto"
	@echo "   make distclean    - Limpieza completa"
	@echo "   make debug        - Compilar en modo depuración"
	@echo "   make release      - Compilar optimizado"
	@echo "   make info         - Mostrar esta información"
	@echo "   make install      - Instalar en sistema"
	@echo "   make uninstall    - Desinstalar"
	@echo "   make package      - Crear paquete ZIP"
	@echo "   make check        - Verificar sintaxis"
	@echo "   make depend       - Generar dependencias"
	@echo "=================================================="

# Verificar sintaxis de todos los archivos
check:
	@echo " Verificando sintaxis de archivos C..."
	@echo "=================================================="
	@for file in $(ALL_SOURCES); do \
		echo "Verificando $$file..."; \
		$(CC) $(CFLAGS) -fsyntax-only $$file && \
		echo "   OK" || echo "   ERROR"; \
	done
	@for file in $(ALL_HEADERS); do \
		echo "Verificando $$file..."; \
		$(CC) $(CFLAGS) -fsyntax-only $$file && \
		echo "   OK" || echo "   ERROR"; \
	done
	@echo "=================================================="
	@echo "Verificación completada"

# ========================================================================================================================
# REGLAS DE INSTALACIÓN Y EMPAQUETADO
# ========================================================================================================================

# Instalar en el sistema
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	chmod 755 /usr/local/bin/$(TARGET)
	@echo " Calculadora instalada en /usr/local/bin/$(TARGET)"

# Desinstalar del sistema
uninstall:
	rm -f /usr/local/bin/$(TARGET)
	@echo "  Calculadora desinstalada"

# Crear paquete ZIP del proyecto
package: distclean
	@mkdir -p calc_project/src
	@mkdir -p calc_project/include
	@cp *.c calc_project/src/ 2>/dev/null || true
	@cp *.h calc_project/include/ 2>/dev/null || true
	@cp Makefile README* calc_project/ 2>/dev/null || true
	@zip -r calc_project.zip calc_project/
	@rm -rf calc_project
	@echo " Proyecto empaquetado como calc_project.zip"

# Crear estructura de directorios
create-dirs:
	@mkdir -p src include build
	@echo "  Estructura de directorios creada:"
	@echo "   src/      - Archivos fuente (.c)"
	@echo "   include/  - Archivos cabecera (.h)"
	@echo "   build/    - Archivos objeto (.o)"

# Generar dependencias automáticas
depend:
	@$(CC) -MM $(ALL_SOURCES) > .depend
	@echo "  Dependencias generadas en .depend"

# Incluir dependencias si existen
-include .depend

# ========================================================================================================================
# REGLAS PARA CREAR ARCHIVOS DE CABECERA VACÍOS (Sí aún no los tenemos)
# ========================================================================================================================

create-headers:
	@echo "Creando archivos de cabecera de conversión..."
	@for header in $(CONVERSION_HEADERS); do \
		if [ ! -f $$header ]; then \
			echo "/* $$header */" > $$header; \
			echo "#ifndef $$(echo $$header | tr 'a-z.' 'A-Z_')" >> $$header; \
			echo "#define $$(echo $$header | tr 'a-z.' 'A-Z_')" >> $$header; \
			echo "" >> $$header; \
			echo "/* Prototipos de funciones */" >> $$header; \
			echo "" >> $$header; \
			echo "#endif" >> $$header; \
			echo " $$header creado"; \
		else \
			echo " $$header ya existe"; \
		fi; \
	done
	@echo "Archivos de cabecera listos"

create-sources:
	@echo "Creando archivos fuente de conversión..."
	@for source in $(CONVERSION_SOURCES); do \
		if [ ! -f $$source ]; then \
			header="$$(basename $$source .c).h"; \
			echo "/* $$source */" > $$source; \
			echo "#include <stdio.h>" >> $$source; \
			echo "#include <stdlib.h>" >> $$source; \
			echo "#include <string.h>" >> $$source; \
			echo "#include <ctype.h>" >> $$source; \
			echo "#include \"$$header\"" >> $$source; \
			echo "#include \"stack.h\"" >> $$source; \
			echo "#include \"dlist.h\"" >> $$source; \
			echo "" >> $$source; \
			echo "/* Implementación de funciones */" >> $$source; \
			echo "" >> $$source; \
			echo " $$source creado"; \
		else \
			echo " $$source ya existe"; \
		fi; \
	done
	@echo "Archivos fuente listos"

# ========================================================================================================================
# REGLAS PHONY
# ========================================================================================================================
.PHONY: all clean distclean run help test-conversions test-expr \
        debug release info check install uninstall package \
        create-dirs depend create-headers create-sources
