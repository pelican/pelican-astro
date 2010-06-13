set(data_src
    src/AntennaPositions.cpp
    src/CorrectedVisibilityData.cpp
    src/FlagTable.cpp
    src/ImageData.cpp
    src/ModelVisibilityData.cpp
    src/VisibilityData.cpp
    src/VisibilityPositions.cpp
)

include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTXML_INCLUDE_DIR}
)

add_library(data ${data_src})

target_link_libraries(data
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test directory.
#add_subdirectory(test)
