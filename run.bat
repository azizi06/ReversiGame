@echo off

:: Run the cmake build command
cmake --build build
:: Check if the command was successful
if %ERRORLEVEL% equ 0 (
    echo CMake build succeeded
    .\build\REVERSIGAME

) else (
    echo CMake build failed
)

