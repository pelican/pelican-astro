# Declare the 'modulesTest' sub-package which depends on modules.
SUBPACKAGE(modulesTest modules)

# Declare the list of sources to be build.
set(modulesTest_src
    src/modulesTest.cpp
    src/AstrometryFastTest.cpp
    src/BasicFlaggerTest.cpp
    src/ZenithImagerDftTest.cpp
    src/ZenithModelVisibilitiesTest.cpp
    src/ImageWriterFitsTest.cpp
    ##src/ZenithCalibraterTest.cpp
)

# Create a sub-package binary.
add_executable(modulesTest ${modulesTest_src})

# Link the against the required sub-package libraries and the CppUnit library.
target_link_libraries(modulesTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)

# Add the sub-package binary to the test suite.
add_test(modulesTest modulesTest)
