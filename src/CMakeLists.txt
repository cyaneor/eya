cmake_minimum_required(VERSION 3.12)
project(${CMAKE_PROJECT_NAME}_lib
        VERSION 1.0.0
        DESCRIPTION "Efficient Yet Abstractive"
        LANGUAGES C)

# -------------------------------------------------------------------------------------------- #
# Compiler Configuration                                                                       #
# -------------------------------------------------------------------------------------------- #

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -------------------------------------------------------------------------------------------- #
# Global Configuration                                                                         #
# -------------------------------------------------------------------------------------------- #

# Allow others to reduce the path if it is required
if(NOT DEFINED EYA_LIB_ROOT_DIR)
    # The path to the current catalog of the source files of the project
    set(EYA_LIB_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# -------------------------------------------------------------------------------------------- #
# Directory Setup                                                                              #
# -------------------------------------------------------------------------------------------- #

# Configure key library directories
set(EYA_LIB_INCLUDE_DIR "${EYA_LIB_ROOT_DIR}/inc")       # Library headers location
set(EYA_LIB_SOURCE_DIR "${EYA_LIB_ROOT_DIR}/src")        # Source code directory
set(EYA_CMAKE_EXTENSION_DIR ${EYA_LIB_ROOT_DIR}/cmake)   # CMake helpers root

# Specialized CMake subdirectories
set(EYA_CMAKE_EXTENSION_OPTIONS_DIR ${EYA_CMAKE_EXTENSION_DIR}/options)  # Build options
set(EYA_CMAKE_EXTENSION_MODULES_DIR ${EYA_CMAKE_EXTENSION_DIR}/module)   # CMake modules

# -------------------------------------------------------------------------------------------- #
# Build Configuration Options                                                                  #
# -------------------------------------------------------------------------------------------- #

# Core build system initialization
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/clear_options.cmake)          # Reset build flags
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/library_options.cmake)        # Feature toggles

# Compiler flags configuration
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/compiler_common_options.cmake)  # Base flags
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/compiler_debug_options.cmake)   # Debug settings
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/compiler_release_options.cmake) # Release optimizations

# -------------------------------------------------------------------------------------------- #
# Build System Modules                                                                         #
# -------------------------------------------------------------------------------------------- #

# Configuration preprocessing
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/collect_library_options.cmake)   # Option aggregation
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/compile_definitions.cmake)       # Platform defines
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/collect_compile_options.cmake)   # Flags collection
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/parse_version.cmake)             # Version parsing
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/check_type_size.cmake)           # Type validation
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/source_files.cmake)              # Source management

# -------------------------------------------------------------------------------------------- #
# Library Target Configuration                                                                 #
# -------------------------------------------------------------------------------------------- #

# Primary library construction
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/build_library.cmake)  # Library target creation

# -------------------------------------------------------------------------------------------- #
# Target Properties                                                                            #
# -------------------------------------------------------------------------------------------- #

# Header inclusion setup
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${EYA_LIB_INCLUDE_DIR})

# Compilation definitions
target_compile_definitions(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS}
        PUBLIC ${EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS})

# Compiler flags propagation
target_compile_options(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_COMPILE_OPTIONS}
        PUBLIC ${EYA_TARGET_PUBLIC_COMPILE_OPTIONS})

# Linker configuration
target_link_options(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_LINK_OPTIONS}
        PUBLIC ${EYA_TARGET_PUBLIC_LINK_OPTIONS})