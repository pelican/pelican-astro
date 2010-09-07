#
# dependencies.cmake:
#
# Sets Dependencies:
#   Qt4
#   CppUnit
#   CFitsio
#   Boost program options
#   cblas (either ATLAS or MKL)
#   lapack (either ATLAS or MKL)
#

# === Find Dependencies.
find_package(Boost COMPONENTS program_options REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtNetwork QtXml REQUIRED)
find_package(CFitsio REQUIRED)
find_package(OpenMP REQUIRED)
find_package(Pelican REQUIRED)
find_package(CppUnit REQUIRED)

# === Find cblas and lapack from MKL if availiable, otherwise elsewhere.
if(NOT DEFINED pelican_mkl)
    set(pelican_mkl true)
endif(NOT DEFINED pelican_mkl)

if(pelican_mkl)
    find_package(MKL QUIET)
endif(pelican_mkl)

if (MKL_FOUND)
    add_definitions(-DUSING_MKL)
    set(pelican_math_libs ${MKL_LIBRARIES})
    set(pelican_mkl true)
    include_directories(${MKL_INCLUDE_DIR})
    message(STATUS "FoundMKL: ${pelican_math_libs}")
    #link_directories(
else (MKL_FOUND)
    find_package(CBLAS REQUIRED)
    find_package(LAPACK REQUIRED)
    set(pelican_math_libs ${LAPACK_LIBRARIES} ${CBLAS_LIBRARIES})
endif (MKL_FOUND)

include_directories(
    ${QT_INCLUDE_DIR}
    ${CFITSIO_INCLUDE_DIR}
)
