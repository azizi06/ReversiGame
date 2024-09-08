cmake_minimum_required(VERSION 3.30)
project(REVERSIGAME)

# Define the source files

include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME}
    raylib
    opengl32
    gdi32
    winmm
)