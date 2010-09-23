# Declare the 'adapters' sub-package that depends on the data sub-package.
SUBPACKAGE(adapters data)

# Declare the list of source to be build for this sub-package.
set(adapters_SRC
    src/AdapterAntennaList.cpp
    src/AdapterLofarStationVisibilities.cpp
)

# Create the sub-package library from the listed sources.
SUBPACKAGE_LIBRARY(adapters ${adapters_SRC})

# Register the external dependencies of the sub-package.
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test sub-directory.
add_subdirectory(test)

