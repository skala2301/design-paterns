# ============================================================================
# Configuración Básica del Proyecto
# ============================================================================
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y versión
project(WeatherStation VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# Estándar de C++ y Configuraciones del Compilador
# ============================================================================
set(CMAKE_CXX_STANDARD 17)                  # C++11, 14, 17, 20, 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)         # Obligatorio usar el estándar
set(CMAKE_CXX_EXTENSIONS OFF)               # Desactiva extensiones específicas del compilador

# Tipo de build por defecto (Debug o Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ============================================================================
# Flags de Compilación (Opcionales pero recomendados)
# ============================================================================
# Flags para Debug
#set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic")

# Flags para Release
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# ============================================================================
# Directorios de Include
# ============================================================================
# Añade directorios donde están tus archivos .h
include_directories(
    ${CMAKE_SOURCE_DIR}           # Raíz del proyecto
    ${CMAKE_SOURCE_DIR}/include   # Carpeta de headers
    # ${CMAKE_SOURCE_DIR}/lib      # Si tienes librerías propias
)

# ============================================================================
# Recolección de Archivos Fuente
# ============================================================================

# Opción 1: Listar archivos manualmente (más control)
#set(SOURCES
#    src/main.cpp
#    lib/Store/store.cpp
#)

# Opción 2: Recolectar automáticamente (más flexible)
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "lib/**/*.cpp"
)

# Opción 3: Headers (opcional, para que aparezcan en IDEs)
# file(GLOB_RECURSE HEADERS 
#     "include/*.h"
#     "lib/**/*.h"
# )

# ============================================================================
# Crear Ejecutable
# ============================================================================
add_executable(${PROJECT_NAME} ${SOURCES})

# Si tienes headers, añádelos para que aparezcan en el IDE
# target_sources(${PROJECT_NAME} PRIVATE ${HEADERS})

# ============================================================================
# Linkear Librerías del Sistema (si las necesitas)
# ============================================================================
# Ejemplo: pthread para multi-threading
# target_link_libraries(${PROJECT_NAME} pthread)

# Ejemplo: math library
# target_link_libraries(${PROJECT_NAME} m)

# ============================================================================
# Buscar y Linkear Librerías Externas (Ejemplos comunes)
# ============================================================================

# Boost
# find_package(Boost REQUIRED COMPONENTS system filesystem)
# target_link_libraries(${PROJECT_NAME} Boost::system Boost::filesystem)

# OpenCV
# find_package(OpenCV REQUIRED)
# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Qt5
# find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
# target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)

# SQLite3
# find_package(SQLite3 REQUIRED)
# target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)

# CURL
# find_package(CURL REQUIRED)
# target_link_libraries(${PROJECT_NAME} CURL::libcurl)

# ============================================================================
# Opciones de Compilación Adicionales
# ============================================================================

# Mostrar todos los warnings
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

# Habilitar sanitizers para debugging (opcional)
# target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)
# target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address -fsanitize=undefined)

# ============================================================================
# Instalación (opcional)
# ============================================================================
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# ============================================================================
# Testing (opcional - requiere Google Test u otro framework)
# ============================================================================
# enable_testing()
# add_subdirectory(tests)

# ============================================================================
# Mensaje de Información
# ============================================================================
message(STATUS "")
message(STATUS "Configuración del Proyecto:")
message(STATUS "  Nombre:        ${PROJECT_NAME}")
message(STATUS "  Versión:       ${PROJECT_VERSION}")
message(STATUS "  Build Type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compilador:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  C++ Standard:  C++${CMAKE_CXX_STANDARD}")
message(STATUS "")