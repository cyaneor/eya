# ---------------------------------------------------------------------------------------- #
# CMake options processing function                                                        #
#                                                                                          #
# This function filters a list of CMake options based on specified prefix and value.       #
# Options matching the criteria can be collected in an output list.                        #
#                                                                                          #
# Parameters:                                                                              #
#   OPTION_PREFIX  - Prefix that options should start with (single value)                  #
#   OPTION_VALUE   - Required value for matching options (single value)                    #
#   OUTPUT_LIST    - Name of the output variable to store matching options (optional)      #
#   OPTION_LIST    - List of options to process (multi-value)                              #
# ---------------------------------------------------------------------------------------- #
function(process_cmake_options)
    # Parse function arguments
    set(oneValueArgs OPTION_PREFIX OPTION_VALUE OUTPUT_LIST)
    set(multiValueArgs OPTION_LIST)
    cmake_parse_arguments(ARGS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Check required parameters
    if (NOT ARGS_OPTION_LIST OR NOT ARGS_OPTION_PREFIX OR NOT DEFINED ARGS_OPTION_VALUE)
        message(FATAL_ERROR "Missing required parameters: OPTION_LIST, OPTION_PREFIX or OPTION_VALUE")
    endif ()
    
    # Process all options
    foreach (CURRENT_OPTION IN ITEMS ${ARGS_OPTION_LIST})
        # Check prefix and value match
        if (CURRENT_OPTION MATCHES "^${ARGS_OPTION_PREFIX}.*" AND ${CURRENT_OPTION} STREQUAL "${ARGS_OPTION_VALUE}")
            # Display option information
            message(STATUS "  • ${CURRENT_OPTION}")

            # Add to output list if specified
            if (ARGS_OUTPUT_LIST)
                list(APPEND ${ARGS_OUTPUT_LIST} ${CURRENT_OPTION})
            endif ()
        endif ()
    endforeach ()

    # Save the resulting list if specified
    if (ARGS_OUTPUT_LIST)
        set(${ARGS_OUTPUT_LIST} ${${ARGS_OUTPUT_LIST}} PARENT_SCOPE)
    endif ()
endfunction()