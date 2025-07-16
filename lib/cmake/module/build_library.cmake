# -------------------------------------------------------------------------------------- #
# Target type configuration                                                              #
#                                                                                        #
# This script determines the build artifact type based on user options:                  #
# - Static library when EYA_LIBRARY_OPTION_STATIC_BUILD is enabled                       #
# - Shared library when EYA_LIBRARY_OPTION_SHARED_BUILD is enabled                       #
# - Executable by default if neither library option is selected                          #
# -------------------------------------------------------------------------------------- #

# Verify static build option value
if (EYA_LIBRARY_OPTION_STATIC_BUILD)
    # Create static library from source files when static build enabled
    add_library(${CMAKE_PROJECT_NAME} STATIC ${EYA_TARGET_SOURCE_FILES})
elseif (EYA_LIBRARY_OPTION_SHARED_BUILD)
    # Create shared library from source files when dynamic build enabled
    add_library(${CMAKE_PROJECT_NAME} SHARED ${EYA_TARGET_SOURCE_FILES})
else ()
    # Create executable as fallback when no library options are specified
    add_executable(${CMAKE_PROJECT_NAME} ${EYA_TARGET_SOURCE_FILES})
endif ()