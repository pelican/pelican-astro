SUBPACKAGE(modulesTest modules)
set(modulesTest_src
    src/modulesTest.cpp
    src/AstrometryFastTest.cpp
    src/BasicFlaggerTest.cpp
    src/ZenithImagerDftTest.cpp
    src/ZenithModelVisibilitiesTest.cpp
    src/ImageWriterFitsTest.cpp
)
add_executable(modulesTest ${modulesTest_src})
target_link_libraries(modulesTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)
add_test(modulesTest modulesTest)
