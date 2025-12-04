
# ED2025 – Convertidor de Expresiones Algebraicas  
### Proyecto Final – Estructuras de Datos  

Autora: Olvera García Nadia 32207473-0


## Descripción General

Este proyecto es una herramienta desarrollada en lenguaje C que permite convertir expresiones algebraicas entre notaciones infija, postfija y prefija.  
Incluye además manejo de estructuras de datos fundamentales, lectura y procesamiento de expresiones, almacenamiento de historial y estadísticas de uso.

El diseño modular del proyecto facilita su mantenimiento, escalabilidad y análisis académico.


## Estructura del Proyecto

```bash
PROYECTO_FINAL/
│
├── main/                          # Código fuente principal
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
│
├── include/                       # Archivos de encabezado
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
│
└── compile.bat                    # Script de compilación para Windows



````

El proyecto está organizado en módulos independientes que permiten separar claramente cada funcionalidad, siguiendo buenas prácticas de programación estructurada en C.

---

## Compilación

### Método manual (Windows)

1. Abrir la terminal y ubicarse en el directorio del proyecto:

```bash
cd "C:\Users\nadia\OneDrive\Escritorio\ED2025-Nadia-main (14)\ED2025-Nadia-main\PROYECTO_FINAL"
````

2. Compilar el proyecto usando GCC:

```bash
gcc -Iinclude main/*.c -o calc.exe -lm
```

3. Ejecutar el programa según la opción deseada:

| Acción           | Comando       |
| ---------------- | ------------- |
| Modo interactivo | .\calc.exe    |
| Mostrar ayuda    | .\calc.exe -h |
| Mostrar versión  | .\calc.exe -v |
| Mostrar créditos | .\calc.exe -c |

---

## Funcionalidades Disponibles

### Conversión entre notaciones

1. Infija a Postfija
2. Infija a Prefija
3. Postfija a Infija
4. Postfija a Prefija
5. Prefija a Infija
6. Prefija a Postfija

### Otras funciones

7. Evaluar expresión (pendiente de implementación)
8. Mostrar historial
9. Mostrar estadísticas
10. Limpiar historial
11. Créditos
12. Salir

---

## Módulos Implementados

| Módulo       | Descripción                                                                             |
| ------------ | --------------------------------------------------------------------------------------- |
| stack        | Implementación de pilas usadas en conversiones y validación de expresiones              |
| list / dlist | Manejo de listas simples y doblemente enlazadas para historial y estructuras auxiliares |
| parser       | Lectura, separación y validación de expresiones algebraicas                             |
| file_manager | Gestión de archivos para almacenar historial                                            |
| utils        | Funciones de apoyo y utilidades generales                                               |
| conversion_* | Implementación de cada conversión entre infija, postfija y prefija                      |

---

## Objetivo Académico

Este proyecto forma parte del curso de Estructuras de Datos y busca demostrar:

* Manejo de pilas, listas simples y doblemente enlazadas
* Programación modular en C
* Conversión entre notaciones algebraicas
* Manejo de archivos y persistencia de datos
* Construcción de un sistema con menú interactivo

---

## Autora

Nadia Olvera García
Proyecto desarrollado durante el curso ED2025

---




