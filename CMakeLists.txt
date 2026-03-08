cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto
project(typit VERSION 1.0 LANGUAGES CXX)

# Especificar la versión de C++ que se usará
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Añadir todos los archivos fuente automáticamente
# file(GLOB SOURCES "src/*.cpp src/menu/*.cpp src/menu/render/*.cpp")
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/player.cpp
    src/render.cpp
    src/menu/menu.cpp
    src/menu/number_menu.cpp
    src/menu/option_menu.cpp
    src/menu/render/menu_render.cpp
    src/menu/render/menu_render_number.cpp
    src/menu/render/menu_render_options.cpp
)
if(WIN32)
    list(APPEND SOURCES src/terms/term-windows.cpp)
else()
    list(APPEND SOURCES src/terms/term-linux.cpp)
endif()

# Crear el ejecutable
add_executable(typit ${SOURCES})

# Incluir el directorio de cabeceras
target_include_directories(typit PRIVATE src)
