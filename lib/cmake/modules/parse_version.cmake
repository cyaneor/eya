# ---------------------------------------------------------------------------------------- #
# Version parsing function                                                                 #
#                                                                                          #
# This function converts a version string into its components (major, minor, and patch).   #
# The parsed components are returned via output variables.                                 #
# ---------------------------------------------------------------------------------------- #
function(parse_version version major_var minor_var patch_var)
    # Replaces dots in the version string with semicolons to create a list.
    # For example, "1.2.3" -> "1;2;3".
    string(REPLACE "." ";" version_list ${version})

    # Gets the first list item (major version).
    list(GET version_list 0 major)

    # Gets the second list item (minor version).
    list(GET version_list 1 minor)

    # Gets the third list item (patch version).
    list(GET version_list 2 patch)

    # Return the components through the output variables
    set(${major_var} ${major} PARENT_SCOPE)
    set(${minor_var} ${minor} PARENT_SCOPE)
    set(${patch_var} ${patch} PARENT_SCOPE)
endfunction()