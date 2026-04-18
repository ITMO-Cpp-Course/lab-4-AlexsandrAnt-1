cmake_minimum_required(VERSION 3.20)
project(Lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # 20-го стандарта более чем достаточно
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции
option(STRICT_WARNINGS "Enable extra warnings" ON)
option(ENABLE_SANITIZERS "Enable AddressSanitizer" ON)

# Интерфейсная библиотека для варнингов (БЕЗ файлов .cpp)
add_library(project_warnings INTERFACE)
if (MSVC)
    target_compile_options(project_warnings INTERFACE /W4 /permissive- $<$<BOOL:${STRICT_WARNINGS}>:/WX>)
else ()
    target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic $<$<BOOL:${STRICT_WARNINGS}>:-Werror>)
endif ()

# Интерфейсная библиотека для санитайзеров (БЕЗ файлов .cpp)
add_library(project_sanitizers INTERFACE)
if (ENABLE_SANITIZERS AND NOT WIN32)
    target_compile_options(project_sanitizers INTERFACE $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer>)
    target_link_options(project_sanitizers INTERFACE $<$<CONFIG:Debug>:-fsanitize=address>)
endif ()

include(CTest)
enable_testing()

# Подключаем папки
add_subdirectory(src/resource_core)
add_subdirectory(tests)