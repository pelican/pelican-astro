# Declare the sub-package data that depends on no other sub-packges.
SUBPACKAGE(data)

# Set the list of source files that should be build for the data sub-package.
set(data_src
    src/AstroDataBlob.cpp
    src/AntennaPositions.cpp
    src/CorrectedVisibilityData.cpp
    src/FlagTable.cpp
    src/ImageData.cpp
    src/ModelVisibilityData.cpp
    src/VisibilityData.cpp
    src/VisibilityPositions.cpp
)

# Create the sub-package library data from the listed sources.
SUBPACKAGE_LIBRARY(data ${data_src})

# Register the external dependencies of the sub-package.
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test sub-directory.
add_subdirectory(test)
