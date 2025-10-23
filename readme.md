# Manual de Usuario

##  Descripción General
Este proyecto ha sido desarrollado en **C++** y puede compilarse directamente desde la terminal de **MSYS2 (UCRT64)**.  
Incluye todos los módulos y archivos fuente necesarios para ejecutar correctamente el programa.  

El sistema utiliza programación orientada a objetos, con clases para representar las piezas, el tablero y la lógica del juego.  
Su estructura modular permite una fácil comprensión, mantenimiento y futuras ampliaciones.

---

##  Requisitos Previos

Antes de compilar y ejecutar el programa, asegúrate de tener instalado:

1. **MSYS2** con el entorno **UCRT64**.  
    Puedes verificarlo abriendo la terminal:
    ```bash
    C:\msys64\ucrt64.exe

2. El compilador g++ y las herramientas de desarrollo:
    pacman -Syu
    pacman -S mingw-w64-ucrt-x86_64-gcc

3. Estar dentro del entorno UCRT64 (no MSYS ni MINGW32):
    echo $MSYSTEM

## Structura del proyecto

 proyecto-ajedrez
 ┣  main.cpp
 ┣ src/
 ┃ ┣ board.cpp
 ┃ ┣ game.cpp
 ┃ ┣ player.cpp
 ┃ ┣ pieces.cpp
 ┃ ┗ gui.cpp
 ┣  include/
 ┃ ┣ board.h
 ┃ ┣ game.h
 ┃ ┣ player.h
 ┃ ┗ pieces.h
 ┗  README.md

## Compilación

En el documento build_instructions está descrito como compilar en la terminal
