SUBPACKAGE(adapters)
set(adapters_SRC
    src/AdapterAntennaList.cpp
    src/AdapterLofarStationVisibilities.cpp
)

SUBPACKAGE_LIBRARY(adapters ${adapters_SRC})
#message(STATUS ">>>>>>>>>>>> adapters sub libs: ${PELICAN_LIBRARY}")
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test directory.
add_subdirectory(test)

