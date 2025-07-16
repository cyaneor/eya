# -------------------------------------------------------------------------------------- #
# Custom build option handling                                                           #
#                                                                                        #
# This script retrieves all variables (options), checks them against                     #
# a specified pattern, and adds enabled options to private compile definitions.          #
# -------------------------------------------------------------------------------------- #

# Retrieve all variables (options) in current CMake directory
get_property(CMAKE_OPTIONS DIRECTORY PROPERTY VARIABLES)

# Process all found options
message(STATUS "Listing all enabled configuration options:")
foreach (CMAKE_OPTION IN ITEMS ${CMAKE_OPTIONS})
    # Check if option name matches "^EYA_LIBRARY_OPTION_.*" pattern 
    # and value is not "OFF". If true, add to compile definitions.
    if (CMAKE_OPTION MATCHES "^EYA_LIBRARY_OPTION_.*" AND NOT ${CMAKE_OPTION} STREQUAL "OFF")
        # Print option key with formatting
        message(STATUS "  • ${CMAKE_OPTION}")
        # Add option to EYA_PRIVATE_COMPILE_DEFINITIONS list
        list(APPEND EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS ${CMAKE_OPTION})
    endif ()
endforeach ()