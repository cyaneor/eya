# Minimum required CMake version
# Using a relatively recent version to support modern features
cmake_minimum_required(VERSION 3.12)

# Initialize project named "eya"
# Defines basic project settings and controls build targets
project(eya
        VERSION 1.0.0
        DESCRIPTION "Efficient Yet Abstractive")

#-------------------------------------------------------------------------------
# Options
#-------------------------------------------------------------------------------

# Option to control test project builds
# Can be modified via GUI (ccmake/cmake-gui) or command line (-DEYA_TESTS_BUILD=OFF)
option(EYA_TESTS_BUILD "Build test projects" ON)

# Option to control documentation builds
# Can be modified via GUI (ccmake/cmake-gui) or command line (-DEYA_DOCS_BUILD=OFF)
option(EYA_DOCS_BUILD "Build documentation" ON)

#-------------------------------------------------------------------------------
# CMake configuration
#-------------------------------------------------------------------------------

# Check if CMake 3.5 is available (for compatibility)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.5)
    # Turning on or disconnecting of the output data of compilation commands during creation.
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

#-------------------------------------------------------------------------------
# Project path configuration
#-------------------------------------------------------------------------------

if (NOT DEFINED EYA_ROOT_DIR)
    # Project root directory (where this CMakeLists.txt is located)
    set(EYA_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif ()

if (NOT DEFINED EYA_LIB_ROOT_DIR)
    # Directory containing library components
    set(EYA_LIB_ROOT_DIR ${EYA_ROOT_DIR}/lib)
endif ()

if (NOT DEFINED EYA_TEST_ROOT_DIR)
    # Directory containing test components
    set(EYA_TEST_ROOT_DIR ${EYA_ROOT_DIR}/test)
endif ()

if (NOT DEFINED EYA_DOCS_ROOT_DIR)
    # Directory containing documentation sources and configuration
    set(EYA_DOCS_ROOT_DIR ${EYA_ROOT_DIR}/docs)
endif ()

#-------------------------------------------------------------------------------
# Subproject inclusion
#-------------------------------------------------------------------------------

# Add library subdirectory (build library components)
add_subdirectory(${EYA_LIB_ROOT_DIR})

# Conditional inclusion of test components
if (EYA_TESTS_BUILD)
    message(STATUS "Enabling tests build")
    add_subdirectory(${EYA_TEST_ROOT_DIR})
else ()
    message(STATUS "Tests build disabled")
endif ()

# Conditional inclusion of documentation components
if (EYA_DOCS_BUILD)
    message(STATUS "Enabling documentation build")
    add_subdirectory(${EYA_DOCS_ROOT_DIR})
else ()
    message(STATUS "Documentation build disabled")
endif ()