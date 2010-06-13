set(adaptersTest_src
    src/adaptersTest.cpp
    src/AdapterLofarStationVisibilitiesTest.cpp
    src/AdapterAntennaListTest.cpp
)

set(adaptersTestLibrary_src
    src/VisGen.cpp
)

add_library(adaptersTestUtilities ${adaptersTestLibrary_src} )

target_link_libraries(adaptersTestUtilities
    pelican
    adapters
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create the test executable.
add_executable(adaptersTest ${adaptersTest_src})
target_link_libraries(adaptersTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)

# Create the visibility generator.
add_executable(testVisGen src/testVisGen.cpp)
target_link_libraries(testVisGen
)

# Add to the adapters test to the test target.
add_test(adaptersTest adaptersTest)

include(CopyFiles)

# Copy the test/data folder to the build tree.
copy_files(${CMAKE_CURRENT_SOURCE_DIR}/data/* . adaptersTestData)
