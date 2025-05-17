# ---------------------------------------------------------------------------------------- #
# Project version configuration                                                            #
#                                                                                          #
# This script converts the project version into its components (major, minor, and          #
# patch versions), caches them, and adds them as macros for use in the code.               #
# This configuration allows accessing the project version in different parts of the build. #
# ---------------------------------------------------------------------------------------- #

# Replaces dots in the project version with semicolons.
# For example, "1.2.3" -> "1;2;3".
string(REPLACE "." ";" EYA_VERSION_LIST ${PROJECT_VERSION})

# Gets the first list item (major version) and stores it in EYA_VERSION_MAJOR.
list(GET EYA_VERSION_LIST 0 EYA_VERSION_MAJOR)

# Gets the second list item (minor version) and stores it in EYA_VERSION_MINOR.
list(GET EYA_VERSION_LIST 1 EYA_VERSION_MINOR)

# Gets the third list item (patch version) and stores it in EYA_VERSION_PATCH.
list(GET EYA_VERSION_LIST 2 EYA_VERSION_PATCH)

# Stores the major version in cache for later use in CMake,
# making it available as a cache variable. The FORCE flag is added
# to override any previously set values.
set(EYA_VERSION_MAJOR ${EYA_VERSION_MAJOR} CACHE STRING "eya major version component" FORCE)

# Stores the minor version in cache.
set(EYA_VERSION_MINOR ${EYA_VERSION_MINOR} CACHE STRING "eya minor version component" FORCE)

# Stores the patch version in cache.
set(EYA_VERSION_PATCH ${EYA_VERSION_PATCH} CACHE STRING "eya patch version component" FORCE)

# Adds version values as preprocessor macros
# available during compilation (compile definitions).
#
# This enables using them as EYA_VERSION_MAJOR,
# EYA_VERSION_MINOR, and EYA_VERSION_PATCH in the code.
list(APPEND EYA_TARGET_PRIVATE_COMPILE_DEFINITIONS
        EYA_VERSION_MAJOR=${EYA_VERSION_MAJOR}
        EYA_VERSION_MINOR=${EYA_VERSION_MINOR}
        EYA_VERSION_PATCH=${EYA_VERSION_PATCH}
)

# Clears temporary variables EYA_VERSION_MAJOR, EYA_VERSION_MINOR, and EYA_VERSION_PATCH,
# as they are no longer needed in the global CMake scope.
unset(EYA_VERSION_MAJOR)
unset(EYA_VERSION_MINOR)
unset(EYA_VERSION_PATCH)