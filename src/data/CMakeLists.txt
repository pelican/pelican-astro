include_directories(${PELICAN_INCLUDE_DIR})
SUBPACKAGE(data)
set(data_src
    src/AntennaPositions.cpp
    src/CorrectedVisibilityData.cpp
    src/FlagTable.cpp
    src/ImageData.cpp
    src/ModelVisibilityData.cpp
    src/VisibilityData.cpp
    src/VisibilityPositions.cpp
)

SUBPACKAGE_LIBRARY(data ${data_src})
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${QT_QTCORE_LIBRARY}
    ${PELICAN_LIBRARY}
)

# Recurse into test directory.
#add_subdirectory(test)
