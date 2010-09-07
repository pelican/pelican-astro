SUBPACKAGE(utility)
set(utility_src
    src/AstroConfig.cpp
)

SUBPACKAGE_LIBRARY(utility ${utility_src})
SUBPACKAGE_SET_EXTERNAL_LIBRARIES(
    ${QT_QTCORE_LIBRARY}
)

# Recurse into test directory.
#add_subdirectory(test)
