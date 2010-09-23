# Declare the utility sub-package that depends on no other sub-packges.
SUBPACKAGE(utility)

# Set the list of source files that should be build for the utility sub-package.
set(utility_src
    src/AstroConfig.cpp
)

# Create the sub-package library from the listed sources.
SUBPACKAGE_LIBRARY(utility ${utility_src})

# Register the external dependencies of the sub-package.
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test sub-directory.
#add_subdirectory(test)
