# Define the project with variables for name, version, description, and using C language
project(${CMAKE_PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        DESCRIPTION ${PROJECT_DESCRIPTION}
        LANGUAGES C)

# -------------------------------------------------------------------------------------------- #
# Compiler Configuration                                                                       #
# -------------------------------------------------------------------------------------------- #

# Set C language standard to C11
set(CMAKE_C_STANDARD 11)
# Require C11 standard (fail if compiler doesn't support it)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -------------------------------------------------------------------------------------------- #
# Global Configuration                                                                         #
# -------------------------------------------------------------------------------------------- #

# Allow others to override the root directory if needed
if (NOT DEFINED EYA_LIB_ROOT_DIR)
    # Set default root directory to current source directory
    set(EYA_LIB_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
endif ()

# -------------------------------------------------------------------------------------------- #
# Directory Setup                                                                              #
# -------------------------------------------------------------------------------------------- #

# Set path to library header files
set(EYA_LIB_INCLUDE_DIR "${EYA_LIB_ROOT_DIR}/inc")       # Library headers location
set(EYA_LIB_SOURCE_DIR "${EYA_LIB_ROOT_DIR}/src")        # Source code directory
set(EYA_CMAKE_EXTENSION_DIR ${EYA_LIB_ROOT_DIR}/cmake)   # CMake helpers root

# Set path to build option configuration files
set(EYA_CMAKE_EXTENSION_OPTIONS_DIR ${EYA_CMAKE_EXTENSION_DIR}/options)  # Build options
set(EYA_CMAKE_EXTENSION_MODULES_DIR ${EYA_CMAKE_EXTENSION_DIR}/modules)  # CMake modules

# -------------------------------------------------------------------------------------------- #
# Build Configuration Options                                                                  #
# -------------------------------------------------------------------------------------------- #

include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/library_options.cmake) # Library feature flags and build configurations
include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/build_options.cmake) # Compiler settings (optimizations, warnings, etc.)

# -------------------------------------------------------------------------------------------- #
# Build System Modules                                                                         #
# -------------------------------------------------------------------------------------------- #

include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/process_cmake_options.cmake)     # Option aggregation
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/process_compile_options.cmake)   # Flags parsing
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/numeric_limits.cmake)            # Numeric limits
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/parse_version.cmake)             # Version parsing
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/source_files.cmake)              # Source management

# -------------------------------------------------------------------------------------------- #
# Base Target Configuration                                                                    #
# -------------------------------------------------------------------------------------------- #

# Display active library features
get_property(CMAKE_OPTIONS DIRECTORY PROPERTY VARIABLES)
message(STATUS "Library options:")
process_cmake_options(
        OPTION_LIST ${CMAKE_OPTIONS}
        OPTION_PREFIX "EYA_LIBRARY_OPTION_"
        OUTPUT_WITH_VALUES TRUE
        EXCLUDE_OFF TRUE
        OUTPUT_LIST EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS
)

# Parse project version into major, minor, and patch components
parse_version(${CMAKE_PROJECT_VERSION} EYA_VERSION_MAJOR EYA_VERSION_MINOR EYA_VERSION_PATCH)
list(APPEND EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS
        EYA_VERSION_MAJOR=${EYA_VERSION_MAJOR}
        EYA_VERSION_MINOR=${EYA_VERSION_MINOR}
        EYA_VERSION_PATCH=${EYA_VERSION_PATCH})

# Generation numeric sizes and limits
generate_numeric_limits()

# Get all current compile options
get_property(EYA_COMPILE_OPTIONS DIRECTORY PROPERTY VARIABLES)
process_compile_options(
        "${EYA_COMPILE_OPTIONS}"
        "${CMAKE_C_COMPILER_ID}"
        EYA_TARGET_PRIVATE_COMPILE_OPTIONS
        EYA_TARGET_PRIVATE_LINK_OPTIONS
        EYA_TARGET_PRIVATE_LINK_LIBRARIES
)

# Display active compilation features
message(STATUS "Compilation features:")
process_cmake_options(
        OPTION_LIST ${EYA_COMPILE_OPTIONS}
        OPTION_PREFIX "EYA_COMPILE_OPTION_"
        OUTPUT_WITH_VALUES TRUE
        EXCLUDE_OFF TRUE
        OUTPUT_LIST EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS)

# -------------------------------------------------------------------------------------------- #
# Library Target Configuration                                                                 #
# -------------------------------------------------------------------------------------------- #

# Include module to build the library target
include(${EYA_CMAKE_EXTENSION_MODULES_DIR}/build_library.cmake)  # Library target creation

# -------------------------------------------------------------------------------------------- #
# Target Properties                                                                            #
# -------------------------------------------------------------------------------------------- #

# Set include directories for the target
target_include_directories(${CMAKE_PROJECT_NAME}
        PUBLIC ${EYA_LIB_INCLUDE_DIR})

# Set compile definitions for the target
target_compile_definitions(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS}
        PUBLIC ${EYA_TARGET_PUBLIC_COMPILE_DEFINITIONS})

# Set compiler options for the target
target_compile_options(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_COMPILE_OPTIONS}
        PUBLIC ${EYA_TARGET_PUBLIC_COMPILE_OPTIONS})

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    # Set linker options for the target
    target_link_options(${CMAKE_PROJECT_NAME}
            PRIVATE ${EYA_TARGET_PRIVATE_LINK_OPTIONS}
            PUBLIC ${EYA_TARGET_PUBLIC_LINK_OPTIONS})
endif ()

# Set linked libraries for the target
target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE ${EYA_TARGET_PRIVATE_LINK_LIBRARIES}
        PUBLIC ${EYA_TARGET_PUBLIC_LINK_LIBRARIES})