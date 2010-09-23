# Declare a sub-package called dataTest that depends on the data sub-package.
SUBPACKAGE(dataTest data)

# Declare the list of sources to be build for this sub-package.
set(dataTest_src
    src/dataTest.cpp
    src/ImageDataTest.cpp
    src/VisibilityDataTest.cpp
    src/FlagTableTest.cpp
    src/VisibilityPositionsTest.cpp
    src/AntennaPositionsTest.cpp
)

# Create an executable for the sub-package.
add_executable(dataTest ${dataTest_src})

# Link the executable with the the dependent sub-package libraries and the
# CppUnit library.
target_link_libraries(dataTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)

# Add the executable to the unit testing suite.
add_test(dataTest dataTest)
