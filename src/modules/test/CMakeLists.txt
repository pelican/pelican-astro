set(modulesTest_src
    src/modulesTest.cpp
    src/AstrometryFastTest.cpp
    src/BasicFlaggerTest.cpp
    src/ZenithImagerDftTest.cpp
    src/ZenithModelVisibilitiesTest.cpp
    src/ImageWriterFitsTest.cpp
)

# Create the modulesTest binary.
add_executable(modulesTest ${modulesTest_src})

target_link_libraries(modulesTest
    ${CPPUNIT_LIBRARIES}
    modules
)

add_test(modulesTest modulesTest)
