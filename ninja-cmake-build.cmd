@echo off
:: Check if the mode (Debug or Release) is provided as a parameter
if "%1"=="" (
    echo "Usage: ./mingw-cmake-build.cmd [debug|release|relwithdebinfo|minsizerel]"
	exit /b 1
)

:: Set the project directory path, change if needed
set PROJECT_DIR=%cd%

:: Set the build directory based on the input parameter (debug or release)
set BUILD_DIR=%PROJECT_DIR%\cmake-build-%1

:: Delete the build directory if it exists
if exist %BUILD_DIR% (
    echo Deleting the existing build directory...
    rmdir /s /q %BUILD_DIR%
)

:: Create the build directory
echo Creating the build directory...
mkdir %BUILD_DIR%

:: Change to the build directory
cd %BUILD_DIR%

:: Run CMake with the necessary parameters based on the selected mode (debug or release)
echo Running CMake for %1...
cmake .. -DCMAKE_BUILD_TYPE=%1 -DEYA_BUILD_TESTS=%2 -DEYA_BUILD_DOCS=%3 -G "Ninja"

:: Build the project
echo Building the project...
cmake --build . --parallel

:: Done
echo Build completed in %1 mode.
cd %PROJECT_DIR%
pause
