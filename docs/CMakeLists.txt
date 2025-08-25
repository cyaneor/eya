# ---------------------------------------------------------------------------------------- #
# Documentation Generation Configuration                                                   #
#                                                                                          #
# This script finds Doxygen and creates a target for generating documentation based on it .#
# It configures the Doxygen configuration file, sets the necessary paths and commands      #
# for automatic project documentation generation.                                          #
# ---------------------------------------------------------------------------------------- #

# Find the Doxygen package, which is used for documentation generation
find_package(Doxygen)

# Check if Doxygen was found
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${EYA_DOCS_ROOT_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Create a custom target for documentation generation
    add_custom_target(${PROJECT_NAME}_docs ALL
            # Command to run Doxygen using the generated configuration file
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            # Specify the working directory for the command
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            # Add a comment that will be displayed when executing the command
            COMMENT "Generating documentation with Doxygen"
            # Specify that commands should be interpreted verbatim
            VERBATIM)
endif ()