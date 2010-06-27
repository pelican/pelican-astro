SUBPACKAGE(adaptersTest adapters)

# Build the adapters test utility library.
# ------------------------------------------------------------------------------
set(adaptersTestLibrary_src
    src/VisGen.cpp
)
SUBPACKAGE_LIBRARY(adaptersTestUtils ${adaptersTestLibrary_src})



# Build the adapters test executable.
# ------------------------------------------------------------------------------
set(adaptersTest_src
    src/adaptersTest.cpp
    src/AdapterLofarStationVisibilitiesTest.cpp
    src/AdapterAntennaListTest.cpp
)
add_executable(adaptersTest ${adaptersTest_src})
target_link_libraries(adaptersTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)
add_test(adaptersTest adaptersTest)



# Create the visibility generator binary.
# ------------------------------------------------------------------------------
add_executable(testVisGen src/testVisGen.cpp)


# Copy the test/data folder to the build tree.
include(CopyFiles)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/data/* . adaptersTestData)
