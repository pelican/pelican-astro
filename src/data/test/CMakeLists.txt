SUBPACKAGE(dataTest data)
set(dataTest_src
    src/dataTest.cpp
    src/ImageDataTest.cpp
    src/VisibilityDataTest.cpp
    src/FlagTableTest.cpp
    src/VisibilityPositionsTest.cpp
    src/AntennaPositionsTest.cpp
)
add_executable(dataTest ${dataTest_src})

message(STATUS "================= ${SUBPACKAGE_LIBRARIES}")
target_link_libraries(dataTest
    ${SUBPACKAGE_LIBRARIES}
    ${CPPUNIT_LIBRARIES}
)
add_test(dataTest dataTest)
