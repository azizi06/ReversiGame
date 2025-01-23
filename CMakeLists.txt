cmake_minimum_required(VERSION 3.30)
project(REVERSIGAME)

# Define the source files
include_directories("./src/include")

add_executable(${PROJECT_NAME} 
src/Utils/map.c
src/Utils/tools.c
src/Utils/moveSet.c
src/Utils/set.c
src/Utils/move.c
src/src/GameLoop.c
src/src/reversi.c
src/src/MinMax.c

src/main.c
)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
