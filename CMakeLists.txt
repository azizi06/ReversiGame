cmake_minimum_required(VERSION 3.30)
project(REVERSIGAME)

# Define the source files
include_directories("./src/include")
include_directories("C:/msys64/mingw64/include")
link_directories("C:/msys64/mingw64/lib")

add_executable(${PROJECT_NAME} 
src/Utils/map.c
src/Utils/tools.c
src/Utils/moveSet.c
src/Utils/set.c
src/Utils/move.c
src/src/GameLoop.c
src/src/reversi.c
src/src/solver.c
src/main.c
)
set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(${PROJECT_NAME}
    raylib
    opengl32
    gdi32
    winmm
)