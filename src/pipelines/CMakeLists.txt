set(pipelines_src
    src/TestPipelineVisibilityPrinter.cpp
    src/TestPipelineServer.cpp
    src/TestPipelineRawImage.cpp
    #src/TestPipelineCalibrateImage.cpp
    src/TestPipelineMultipleImages.cpp
)

include_directories(${QT_INCLUDES})

add_library(pipelines ${pipelines_src} )

target_link_libraries(pipelines
    pelican
    ${QT_QTCORE_LIBRARY}
    adapters
    data
    modules
)

# Recurse into test directory.
add_subdirectory(test)
