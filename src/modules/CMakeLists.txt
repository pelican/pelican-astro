SUBPACKAGE(modules)
set(modules_src
    src/AbstractAstrometry.cpp
    src/AstrometryFast.cpp
    src/VisibilityPrinter.cpp
    src/BasicFlagger.cpp
    src/ZenithModelVisibilities.cpp
    src/ZenithImagerDft.cpp
    src/ImageWriterFits.cpp
    src/ImageCombiner.cpp
)
<
SUBPACKAGE_LIBRARY(modules ${modules_src})
set_target_properties(modules PROPERTIES
    COMPILE_FLAGS "${OpenMP_CXX_FLAGS}"
    LINK_FLAGS "${OpenMP_CXX_FLAGS}"
)
SUBPACKAGE_ADD_EXTERNAL_LIBRARIES(
    ${pelican_math_libs}
    ${PELICAN_LIBRARY}
    ${CFITSIO_LIBRARIES}
)

# Recurse into test directory.
add_subdirectory(test)
