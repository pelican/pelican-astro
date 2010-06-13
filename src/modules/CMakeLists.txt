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


include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
)

add_library(modules ${modules_src})

# Link modules with openmp.
set_target_properties(modules PROPERTIES 
    COMPILE_FLAGS "${OpenMP_CXX_FLAGS}"
    LINK_FLAGS "${OpenMP_CXX_FLAGS}"
)

target_link_libraries(modules
    ${pelican_math_libs}
    ${CFITSIO_LIBRARIES}
)

# Recurse into test directory.
#add_subdirectory(test)
