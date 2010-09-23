# Declare the sub-package 'pipelines' which depends on data, utility, modules.
SUBPACKAGE(pipelines data utility modules)

# Declare the list of sources to be build for this sub-package.
set(pipelines_src
    src/TestPipelineVisibilityPrinter.cpp
    src/TestPipelineServer.cpp
    src/TestPipelineRawImage.cpp
    src/TestPipelineMultipleImages.cpp
    #src/TestPipelineCalibrateImage.cpp
)

# Create the sub-package library.
SUBPACKAGE_LIBRARY(pipelines ${pipelines_src})

# Register external dependencies of the sub-package.
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test sub-directory.
add_subdirectory(test)
