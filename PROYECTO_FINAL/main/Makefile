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
MAIN_SOURCES = main/main.c
MAIN_OBJECTS = $(MAIN_SOURCES:.c=.o)

# Módulos de estructuras de datos
DATA_STRUCT_SOURCES = main/stack.c main/dlist.c
DATA_STRUCT_OBJECTS = $(DATA_STRUCT_SOURCES:.c=.o)
DATA_STRUCT_HEADERS = include/stack.h include/dlist.h

# Módulos de conversión
CONVERSION_SOURCES = \
    main/conversion_infix_postfix.c \
    main/conversion_infix_prefix.c \
    main/conversion_postfix_infix.c \
    main/conversion_postfix_prefix.c \
    main/conversion_prefix_infix.c \
    main/conversion_prefix_postfix.c

CONVERSION_OBJECTS = $(CONVERSION_SOURCES:.c=.o)

CONVERSION_HEADERS = \
    include/conversion_infix_postfix.h \
    include/conversion_infix_prefix.h \
    include/conversion_postfix_infix.h \
    include/conversion_postfix_prefix.h \
    include/conversion_prefix_infix.h \
    include/conversion_prefix_postfix.h

# Módulos de utilidades
UTILS_SOURCES = main/utils.c main/parser.c main/file_manager.c
UTILS_OBJECTS = $(UTILS_SOURCES:.c=.o)
UTILS_HEADERS = include/utils.h include/parser.h include/file_manager.h

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
main/main.o: main/main.c $(ALL_HEADERS)
	$(CC) $(CFLAGS) -Iinclude -c main/main.c -o main/main.o
	@echo " main.c compilado"

# Módulos de estructuras de datos
main/stack.o: main/stack.c include/stack.h
	$(CC) $(CFLAGS) -Iinclude -c main/stack.c -o main/stack.o
	@echo " stack.c compilado"

main/dlist.o: main/dlist.c include/dlist.h
	$(CC) $(CFLAGS) -Iinclude -c main/dlist.c -o main/dlist.o
	@echo " dlist.c compilado"

# Módulos de conversión
main/conversion_infix_postfix.o: main/conversion_infix_postfix.c include/conversion_infix_postfix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_infix_postfix.c -o main/conversion_infix_postfix.o
	@echo " conversion_infix_postfix.c compilado"

main/conversion_infix_prefix.o: main/conversion_infix_prefix.c include/conversion_infix_prefix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_infix_prefix.c -o main/conversion_infix_prefix.o
	@echo " conversion_infix_prefix.c compilado"

main/conversion_postfix_infix.o: main/conversion_postfix_infix.c include/conversion_postfix_infix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_postfix_infix.c -o main/conversion_postfix_infix.o
	@echo " conversion_postfix_infix.c compilado"

main/conversion_postfix_prefix.o: main/conversion_postfix_prefix.c include/conversion_postfix_prefix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_postfix_prefix.c -o main/conversion_postfix_prefix.o
	@echo " conversion_postfix_prefix.c compilado"

main/conversion_prefix_infix.o: main/conversion_prefix_infix.c include/conversion_prefix_infix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_prefix_infix.c -o main/conversion_prefix_infix.o
	@echo " conversion_prefix_infix.c compilado"

main/conversion_prefix_postfix.o: main/conversion_prefix_postfix.c include/conversion_prefix_postfix.h
	$(CC) $(CFLAGS) -Iinclude -c main/conversion_prefix_postfix.c -o main/conversion_prefix_postfix.o
	@echo " conversion_prefix_postfix.c compilado"

# Módulos de utilidades
main/utils.o: main/utils.c include/utils.h
	$(CC) $(CFLAGS) -Iinclude -c main/utils.c -o main/utils.o
	@echo " utils.c compilado"

main/parser.o: main/parser.c include/parser.h
	$(CC) $(CFLAGS) -Iinclude -c main/parser.c -o main/parser.o
	@echo " parser.c compilado"

main/file_manager.o: main/file_manager.c include/file_manager.h
	$(CC) $(CFLAGS) -Iinclude -c main/file_manager.c -o main/file_manager.o
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
	@echo "=================================================="

# Verificar sintaxis de todos los archivos
check:
	@echo " Verificando sintaxis de archivos C..."
	@echo "=================================================="
	@for file in $(ALL_SOURCES); do \
		echo "Verificando $$file..."; \
		$(CC) $(CFLAGS) -Iinclude -fsyntax-only $$file && \
		echo "   OK" || echo "   ERROR"; \
	done
	@for file in $(ALL_HEADERS); do \
		echo "Verificando $$file..."; \
		$(CC) $(CFLAGS) -Iinclude -fsyntax-only $$file && \
		echo "   OK" || echo "   ERROR"; \
	done
	@echo "=================================================="
	@echo "Verificación completada"
