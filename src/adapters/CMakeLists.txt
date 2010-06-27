SUBPACKAGE(adapters)
set(adapters_SRC
    src/AdapterAntennaList.cpp
    src/AdapterLofarStationVisibilities.cpp
)

SUBPACKAGE_LIBRARY(adapters ${adapters_SRC})
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${QT_QTCORE_LIBRARY}
    ${PELICAN_LIBRARY}
)

# Recurse into test directory.
#add_subdirectory(test)

