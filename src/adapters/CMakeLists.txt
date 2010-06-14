set(adapters_SRC
    src/AdapterAntennaList.cpp
    src/AdapterLofarStationVisibilities.cpp
)

include_directories(
    ${QT_QTCORE_INCLUDE_DIR}
)

add_library(adapters ${adapters_SRC})

target_link_libraries(adapters
    data
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test directory.
add_subdirectory(test)

