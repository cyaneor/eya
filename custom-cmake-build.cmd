@echo off
:: Check if the mode (Debug/Release/etc.) is provided
if "%1"=="" (
    echo Usage: %~nx0 [Debug|Release|RelWithDebInfo|MinSizeRel] [Generator]
    echo Example: %~nx0 Release
    echo Example: %~nx0 Debug "Visual Studio 17 2022"
    exit /b 1
)

:: Project directory
set "PROJECT_DIR=%cd%"
set "BUILD_DIR=%PROJECT_DIR%\cmake-build-%1"

:: Generator (default: Ninja)
set "GENERATOR=Ninja"
if not "%~2"=="" set "GENERATOR=%~2"

:: Clean existing build
if exist "%BUILD_DIR%" (
    echo Deleting existing build directory...
    rmdir /s /q "%BUILD_DIR%"
)

:: Create build directory
mkdir "%BUILD_DIR%"
cd /d "%BUILD_DIR%"

echo Configuring for %1 with generator: %GENERATOR%

:: Run CMake
if "%GENERATOR%"=="Ninja" (
    cmake .. -DCMAKE_BUILD_TYPE=%1 -DEYA_BUILD_TESTS=%2 -DEYA_BUILD_DOCS=%3 -G "%GENERATOR%"
) else (
    cmake .. -G "%GENERATOR%"
)

:: Build
echo Building in %1 configuration...
cmake --build . --config %1 --parallel

echo Build completed successfully.
cd /d "%PROJECT_DIR%"
pause