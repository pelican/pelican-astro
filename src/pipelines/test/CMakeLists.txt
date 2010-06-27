SUBPACKAGE(pipelinesTest pipelines)


# Create the pipeline test binary.
set(pipelinesTest_src
    src/pipelinesTest.cpp
    src/TestPipelineVisibilityPrinterTest.cpp
    src/TestPipelineServerTest.cpp
    src/TestPipelineRawImageTest.cpp
    #src/TestPipelineCalibrateImageTest.cpp
    src/TestPipelineMultipleImagesTest.cpp
)
add_executable(pipelinesTest ${pipelinesTest_src})
target_link_libraries(pipelinesTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)
add_test(pipelinesTest pipelinesTest)


# Test Visibility printer pipeline binary.
# ------------------------------------------------------------------------------
set(TestPipelineVisibilityPrinter_src
    src/pipelinesTest.cpp
    src/TestPipelineVisibilityPrinterTest.cpp
)
add_executable(testPipelineVisibilityPrinter
    ${TestPipelineVisibilityPrinter_src}
)
target_link_libraries(testPipelineVisibilityPrinter
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)


# Server testing pipeline.
# ------------------------------------------------------------------------------
set(TestPipelineServer_src
    src/pipelinesTest.cpp
    src/TestPipelineServerTest.cpp
)
add_executable(testPipelineServer
    ${TestPipelineServer_src}
)
target_link_libraries(testPipelineServer
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)


# Raw image generation.
# ------------------------------------------------------------------------------
set(TestPipelineRawImage_src
    src/pipelinesTest.cpp
    src/TestPipelineRawImageTest.cpp
)
add_executable(testPipelineRawImage
    ${TestPipelineRawImage_src}
)
target_link_libraries(testPipelineRawImage
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)


# Image calibration.
# ------------------------------------------------------------------------------
#set(TestPipelineCalibrateImage_src
#    src/pipelinesTest.cpp
#    src/TestPipelineCalibrateImageTest.cpp
#)
#add_executable(testPipelineCalibrateImage ${TestPipelineCalibrateImage_src})
#target_link_libraries(testPipelineCalibrateImage
#    ${SUBPACKAGE_LIBRARIES} ${CPPUNIT_LIBRARIES} memoryTracer)


# removed as its slow and artificial (not really a unit test)
#add_test(pipelinesTest pipelinesTest)



# Multiple image generation.
# ------------------------------------------------------------------------------
set(TestPipelineMultipleImages_src
    src/pipelinesTest.cpp
    src/TestPipelineMultipleImagesTest.cpp
)
add_executable(testPipelineMultipleImages
    ${TestPipelineMultipleImages_src}
)
target_link_libraries(testPipelineMultipleImages
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)

include(CopyFiles)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/data/* . pipeLineTestData)
