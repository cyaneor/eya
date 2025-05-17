# Minimum required CMake version
# Using a relatively recent version to support modern features
cmake_minimum_required(VERSION 3.12)

# Initialize project named "eya"
# Defines basic project settings and controls build targets
project(eya)

# Option to control test project builds
# Can be modified via GUI (ccmake/cmake-gui) or command line (-DEYA_BUILD_TESTS=OFF)
option(EYA_BUILD_TESTS "Build test projects" ON)

#-------------------------------------------------------------------------------
# Project path configuration
#-------------------------------------------------------------------------------

if(NOT DEFINED EYA_ROOT_DIR)
    # Project root directory (where this CMakeLists.txt is located)
    set(EYA_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if(NOT DEFINED EYA_LIB_ROOT_DIR)
    # Directory containing library components
    set(EYA_LIB_ROOT_DIR ${EYA_ROOT_DIR}/src)
endif()

if(NOT DEFINED EYA_TEST_ROOT_DIR)
    # Directory containing test components
    set(EYA_TEST_ROOT_DIR ${EYA_ROOT_DIR}/test)
endif()

#-------------------------------------------------------------------------------
# Subproject inclusion
#-------------------------------------------------------------------------------

# Add library subdirectory (build library components)
add_subdirectory(${EYA_LIB_ROOT_DIR})

# Conditional inclusion of test components
if(EYA_BUILD_TESTS)
    message(STATUS "Enabling tests build")
    add_subdirectory(${EYA_TEST_ROOT_DIR})
else()
    message(STATUS "Tests build disabled")
endif()