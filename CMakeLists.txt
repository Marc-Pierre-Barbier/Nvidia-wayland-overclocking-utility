cmake_minimum_required(VERSION 3.28)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wmaybe-uninitialized -O0")
set(CMAKE_C_FLAGS_DEBUG "-g -Werror -O0")
set(CMAKE_C_FLAGS_RELEASE "-static")

# generate the compile_commands for vscode / clang
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
project(nvoc)

set(SOURCES
	src/main.c
)
add_executable(nvoc ${SOURCES})

target_link_libraries(nvoc "nvidia-ml")

set_property(TARGET nvoc PROPERTY CXX_STANDARD 23)
set_property(TARGET nvoc PROPERTY C_STANDARD 23)
