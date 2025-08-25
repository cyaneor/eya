# ---------------------------------------------------------------------------------------- #
# Build Configuration                                                                      #
#                                                                                          #
# This section orchestrates the selection of compiler flags                                #
# and optimization settings based on the active build type (Debug/Release).                #
# ---------------------------------------------------------------------------------------- #

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/debug_options.cmake)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    include(${EYA_CMAKE_EXTENSION_OPTIONS_DIR}/release_options.cmake)
endif ()