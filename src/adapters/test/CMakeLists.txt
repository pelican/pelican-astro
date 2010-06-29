SUBPACKAGE(adaptersTest adapters)


# Build the adapters test utility library.
# ------------------------------------------------------------------------------
set(adaptersTestLibrary_src
    src/VisGen.cpp
)
#message(STATUS "A ==== adaptersTest: sub libs = ${SUBPACKAGE_LIBRARIES}")
SUBPACKAGE_LIBRARY(adaptersTestUtils ${adaptersTestLibrary_src})
#message(STATUS "B ==== adaptersTest: sub libs = ${SUBPACKAGE_LIBRARIES}")
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${QT_QTCORE_LIBRARY}
)


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
target_link_libraries(testVisGen
    ${SUBPACKAGE_LIBRARIES}
)

# Copy the test/data folder to the build tree.
include(CopyFiles)
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/data/* . adaptersTestData)
