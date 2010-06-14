set(pipelinesTest_src
    src/pipelinesTest.cpp
    src/TestPipelineVisibilityPrinterTest.cpp
    src/TestPipelineServerTest.cpp
    src/TestPipelineRawImageTest.cpp
    #src/TestPipelineCalibrateImageTest.cpp
    src/TestPipelineMultipleImagesTest.cpp
)

# CppUnit test
add_executable(pipelinesTest ${pipelinesTest_src})
target_link_libraries(pipelinesTest
    pipelines
    ${CPPUNIT_LIBRARIES}
)

# Add pipeline test to the CppUnit test Suite.
add_test(pipelinesTest pipelinesTest)


# Copy data files to build directory.
include(CopyFiles)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/data/* . pipeLineTestData)

# ==============================================================================


# Visibility printer pipeline.
set(TestPipelineVisibilityPrinter_src
    src/pipelinesTest.cpp
    src/TestPipelineVisibilityPrinterTest.cpp
)
add_executable(testPipelineVisibilityPrinter 
    ${TestPipelineVisibilityPrinter_src}
)
target_link_libraries(testPipelineVisibilityPrinter
    pipelines
    ${CPPUNIT_LIBRARIES}
)


# Server testing pipeline.
set(TestPipelineServer_src
    src/pipelinesTest.cpp
    src/TestPipelineServerTest.cpp
)
add_executable(testPipelineServer
    ${TestPipelineServer_src}
)
target_link_libraries(testPipelineServer
    pipelines
    ${CPPUNIT_LIBRARIES}
)


# Raw image generation.
set(TestPipelineRawImage_src
    src/pipelinesTest.cpp
    src/TestPipelineRawImageTest.cpp
)
add_executable(testPipelineRawImage 
    ${TestPipelineRawImage_src}
)
target_link_libraries(testPipelineRawImage
    pipelines
    ${CPPUNIT_LIBRARIES}
)


# Image calibration.
#set(TestPipelineCalibrateImage_src
#    src/pipelinesTest.cpp
#    src/TestPipelineCalibrateImageTest.cpp
#)
#add_executable(testPipelineCalibrateImage ${TestPipelineCalibrateImage_src})
#target_link_libraries(testPipelineCalibrateImage
#    ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} memoryTracer)


# Multiple image generation.
set( TestPipelineMultipleImages_src
    src/pipelinesTest.cpp
    src/TestPipelineMultipleImagesTest.cpp
)
add_executable(testPipelineMultipleImages 
    ${TestPipelineMultipleImages_src}
)
target_link_libraries(testPipelineMultipleImages
    pipelines
    ${CPPUNIT_LIBRARIES}
)
