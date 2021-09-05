cmake_minimum_required(VERSION 3.1.0)
project(lmc C)
set(EXE_NAME lmc)

include_directories(src)

set(SOURCES src/main.c src/lmc.c src/misc.c)
add_executable(${EXE_NAME} ${SOURCES} )
set_property(TARGET ${EXE_NAME} PROPERTY C_STANDARD 11)

if(WIN32)
    target_compile_options(${EXE_NAME} PRIVATE)
    target_link_libraries(${EXE_NAME})
endif(WIN32)
if(UNIX)
    target_compile_options(${EXE_NAME} PRIVATE)
    target_link_libraries(${EXE_NAME} SDL2 SDL2_image dl pthread)
endif(UNIX)
