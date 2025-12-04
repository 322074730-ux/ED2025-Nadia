@echo off
echo Compilando calculadora de expresiones...
echo.

REM Compilar todos los archivos
gcc -Iinclude main\main.c main\stack.c main\utils.c main\parser.c main\list.c main\dlist.c main\file_manager.c main\conversion_infix_postfix.c main\conversion_infix_prefix.c main\conversion_postfix_infix.c main\conversion_postfix_prefix.c main\conversion_prefix_infix.c main\conversion_prefix_postfix.c -o calc.exe -lm

REM Verificar si la compilación fue exitosa
if %ERRORLEVEL% EQU 0 (
    echo.
    echo  Compilación exitosa!
    echo.
    echo USO:
    echo   calc.exe                    - Menú interactivo
    echo   calc.exe -h                 - Mostrar ayuda
    echo   calc.exe "A+B" inf-post     - Conversión directa
    echo.
) else (
    echo.
    echo  Error en la compilación
    pause
)
