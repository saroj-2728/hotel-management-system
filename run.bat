@echo off
if not exist "build" mkdir build
gcc src/*.c -I./include -o build/hotel_system.exe
if %ERRORLEVEL% EQU 0 (
    echo Build successful! Running program...
    build\hotel_system.exe
) else (
    echo Build failed!
    pause
)