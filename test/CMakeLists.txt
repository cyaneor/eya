# Define test project configuration
# Uses parent project name with '_test' suffix for clear identification
# Sets C++ as the project language and specifies project version
project(${CMAKE_PROJECT_NAME}_test
        LANGUAGES CXX)

# -------------------------------------------------------------------------------------------- #
# Compiler Configuration                                                                       #
# -------------------------------------------------------------------------------------------- #

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check GCC version if GCC is used
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(REQUIRED_GCC_VERSION 11.2.0)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS REQUIRED_GCC_VERSION)
        message(FATAL_ERROR "GCC version ${CMAKE_CXX_COMPILER_VERSION} is too old. "
                "Required at least GCC ${REQUIRED_GCC_VERSION}.")
    endif ()
endif ()

# -------------------------------------------------------------------------------------------- #
# Options                                                                                      #
# -------------------------------------------------------------------------------------------- #

# Windows-specific configuration for Google Test
# Forces use of shared CRT (DLL runtime) to prevent linkage conflicts
set(gtest_force_shared_crt ON CACHE BOOL
        "Force shared CRT for Google Test (required for Windows compatibility)")

# -------------------------------------------------------------------------------------------- #
# Google Test Integration                                                                      #
# -------------------------------------------------------------------------------------------- #

# Add Google Test subdirectory for test framework integration
add_subdirectory(lib/googletest)

# -------------------------------------------------------------------------------------------- #
# Testing Setup                                                                                #
# -------------------------------------------------------------------------------------------- #

# Enable CMake's testing capabilities
enable_testing()

# -------------------------------------------------------------------------------------------- #
# Test Executable                                                                              #
# -------------------------------------------------------------------------------------------- #

# Create test executable with specified source files
# PROJECT_NAME here refers to ${CMAKE_PROJECT_NAME}_tests from project() command
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/addr.cpp
        src/error.cpp
        src/memory.cpp
        src/date_year.cpp
        src/memory_std.cpp
        src/memory_raw.cpp
        src/memory_range.cpp
        src/numeric_limits.cpp
        src/memory_allocator.cpp
        )

# -------------------------------------------------------------------------------------------- #
# Test Dependencies                                                                            #
# -------------------------------------------------------------------------------------------- #

# Link test executable with dependencies
# PRIVATE linkage keeps implementation details hidden
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        gtest           # Google Test framework
        gtest_main      # Google Test main function
        eya             # Project's main library
        )

# -------------------------------------------------------------------------------------------- #
# Post-Build Processing                                                                        #
# -------------------------------------------------------------------------------------------- #

# Post-build step for Windows DLL handling
# Copies built library to test executable directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:eya>                  # Source library file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>  # Destination directory
        )

# -------------------------------------------------------------------------------------------- #
# Test Registration                                                                            #
# -------------------------------------------------------------------------------------------- #

# Register test executable with CTest
add_test(NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME})