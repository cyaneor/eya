# ----------------------------------------------------------------------------------------- #
# CMake options processing function                                                         #
#                                                                                           #
# This function filters a list of CMake options based on specified prefix and value.        #
# Options matching the criteria can be collected in an output list.                         #
#                                                                                           #
# Parameters:                                                                               #
#   OPTION_PREFIX      - Prefix that options should start with (single value)               #
#   OUTPUT_LIST        - Name of the output variable to store matching options (optional)   #
#   OUTPUT_WITH_VALUES - If set, output will be in NAME=VALUE format (optional)             #
#   EXCLUDE_OFF        - If set, options with value OFF are excluded (optional)             #
#   OPTION_LIST        - List of options to process (multi-value)                           #
# ----------------------------------------------------------------------------------------- #
function(process_cmake_options)
    # Parse function arguments
    set(oneValueArgs OPTION_PREFIX OUTPUT_LIST OUTPUT_WITH_VALUES EXCLUDE_OFF)
    set(multiValueArgs OPTION_LIST)
    cmake_parse_arguments(ARGS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Check required parameters
    if (NOT ARGS_OPTION_LIST OR NOT ARGS_OPTION_PREFIX)
        message(FATAL_ERROR "Missing required parameters: OPTION_LIST or OPTION_PREFIX")
    endif ()

    # Process all options
    foreach (CURRENT_OPTION IN ITEMS ${ARGS_OPTION_LIST})
        # Check prefix match
        if (CURRENT_OPTION MATCHES "^${ARGS_OPTION_PREFIX}.*")
            # Skip this option if EXCLUDE_OFF is enabled and option value is OFF
            # This prevents OFF options from being added to the output list
            if (ARGS_EXCLUDE_OFF AND ${CURRENT_OPTION} STREQUAL "OFF")
                continue()
            endif ()

            # Display option information
            message(STATUS "  • ${CURRENT_OPTION} = ${${CURRENT_OPTION}}")

            # Add to output list if value is not OFF
            if (NOT ${CURRENT_OPTION} STREQUAL "OFF")
                if (ARGS_OUTPUT_LIST)
                    if (ARGS_OUTPUT_WITH_VALUES)
                        # Convert ON to 1 if needed
                        if (${CURRENT_OPTION} STREQUAL "ON")
                            set(VALUE_TO_OUTPUT "1")
                        else ()
                            set(VALUE_TO_OUTPUT "${${CURRENT_OPTION}}")
                        endif ()
                        list(APPEND ${ARGS_OUTPUT_LIST} "${CURRENT_OPTION}=${VALUE_TO_OUTPUT}")
                    else ()
                        list(APPEND ${ARGS_OUTPUT_LIST} ${CURRENT_OPTION})
                    endif ()
                endif ()
            endif ()
        endif ()
    endforeach ()

    # Save the resulting list if specified
    if (ARGS_OUTPUT_LIST)
        set(${ARGS_OUTPUT_LIST} ${${ARGS_OUTPUT_LIST}} PARENT_SCOPE)
    endif ()
endfunction()