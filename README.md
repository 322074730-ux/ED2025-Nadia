# ED2025-Nadia   INSTRUCCIONES PARA EJECUTAR EL PROGRAMA
# ESTRUCTURA
El proyecto tiene la siguiente estructura:
PROYECTO_FINAL/
├── main/
│   ├── main.c
│   ├── stack.c
│   ├── utils.c
│   ├── parser.c
│   ├── list.c
│   ├── dlist.c
│   ├── file_manager.c
│   ├── conversion_infix_postfix.c
│   ├── conversion_infix_prefix.c
│   ├── conversion_postfix_infix.c
│   ├── conversion_postfix_prefix.c
│   ├── conversion_prefix_infix.c
│   └── conversion_prefix_postfix.c
├── Include/ (o include/)
│   ├── stack.h
│   ├── utils.h
│   ├── parser.h
│   ├── list.h
│   ├── dlist.h
│   ├── file_manager.h
│   ├── conversion_infix_postfix.h
│   ├── conversion_infix_prefix.h
│   ├── conversion_postfix_infix.h
│   ├── conversion_postfix_prefix.h
│   ├── conversion_prefix_infix.h
│   └── conversion_prefix_postfix.h
└── compile.bat

# COMPILACION MANUAL
1. Ve al directorio del proyecto
cd "C:\Users\nadia\OneDrive\Escritorio\ED2025-Nadia-main (14)\ED2025-Nadia-main\PROYECTO_FINAL"
2. Compila manualmente:
gcc -Iinclude main/*.c -o calc.exe -lm
3. Prueba los diferentes modos:
Modo interactivo
.\calc.exe
Mostrar ayuda
.\calc.exe -h
Mostrar versión
.\calc.exe -v
Mostrar créditos
.\calc.exe -c
# FUNCIONALIDADES DISPONIBLES
1.Infija a Postfija
2.Infija a Prefija
3.Postfija a Infija
4.Postfija a Prefija
5.Prefija a Infija
6.Prefija a Postfija
7.Evaluar expresión (no implementado aún)
8.Mostrar historial
9.Mostrar estadísticas
10.Limpiar historial
11.Créditos
12.Salir
