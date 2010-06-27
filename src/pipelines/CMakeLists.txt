SUBPACKAGE(pipelines data)
set(pipelines_src
    src/TestPipelineVisibilityPrinter.cpp
    src/TestPipelineServer.cpp
    src/TestPipelineRawImage.cpp
    #src/TestPipelineCalibrateImage.cpp
    src/TestPipelineMultipleImages.cpp
)


SUBPACKAGE_LIBRARY(pipelines ${pipelines_src})
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test directory.
add_subdirectory(test)
