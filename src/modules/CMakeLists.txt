# Declare the 'modules' subpackage that depends on data and utility.
SUBPACKAGE(modules data utility)

# Declare the list of sources to be built for this sub-package.
set(modules_src
    src/AbstractAstrometry.cpp
    src/AstrometryFast.cpp
    src/VisibilityPrinter.cpp
    src/BasicFlagger.cpp
    src/ZenithModelVisibilities.cpp
    src/ZenithImagerDft.cpp
    src/ImageWriterFits.cpp
    src/ImageCombiner.cpp
    ##src/ZenithCalibrater.cpp
)

# Create the sub-package library data from the listed sources.
SUBPACKAGE_LIBRARY(modules ${modules_src})

# Link and compile with OpenMP.
set_target_properties(modules PROPERTIES
    COMPILE_FLAGS "${OpenMP_CXX_FLAGS}"
    LINK_FLAGS "${OpenMP_CXX_FLAGS}"
)

# Register the external depenencies of the sub-package.
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${pelican_math_libs}
    ${PELICAN_LIBRARY}
    ${CFITSIO_LIBRARIES}
)

# Recurse into test sub-directory.
add_subdirectory(test)
