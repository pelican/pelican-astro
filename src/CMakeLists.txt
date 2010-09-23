#===============================================================================
# Top level pelican-astro cmake script.
#===============================================================================
#
# Useful CMake Options:
# ---------------------
#   -DCMAKE_BUILD_TYPE={debug | release} (default: release)
#       Build in debug or release mode.
#
#   -DCMAKE_CXX_COMPILER={compiler} (default: c++)
#       Sets the C++ compiler.
#
#   -DCMAKE_C_COMPILER={compiler} (default: gcc)
#       Sets the C compiler.
#
#===============================================================================

# Specify the minimum cmake version.
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# === Set the project name.
project(pelican-astro CXX C)

# === Set the project version.
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# === CMake setup.
list(INSERT CMAKE_MODULE_PATH 0 ${pelican-astro_SOURCE_DIR}/cmake)
include(cmake/packagemacrosNew.cmake)
enable_testing()

# === Set dependencies.
include(dependencies)

# === Set compiler options.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include(compilerDefaults)

# === Installation locations.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif(NOT CMAKE_BUILD_TYPE)

if(NOT PELICAN_ASTRO_INSTALL_DIR)
    set(PELICAN_ASTRO_INSTALL_DIR "pelican-astro")
endif(NOT PELICAN_ASTRO_INSTALL_DIR )

if(NOT LIBRARY_INSTALL_DIR)
    set(LIBRARY_INSTALL_DIR ${PELICAN_ASTRO_INSTALL_DIR}/lib)
endif(NOT LIBRARY_INSTALL_DIR)

if(NOT BINARY_INSTALL_DIR)
    set(BINARY_INSTALL_DIR ${PELICAN_ASTRO_INSTALL_DIR}/bin)
endif(NOT BINARY_INSTALL_DIR)

if(NOT DOC_INSTALL_DIR)
    set(DOC_INSTALL_DIR ${PELICAN_ASTRO_INSTALL_DIR}/doc)
endif(NOT DOC_INSTALL_DIR)

# === Declare project library to be created from the listed sub-packages.
DECLARE_PROJECT_LIBRARY(pelican-astro
    adapters adaptersTest data modules pipelines)

# === Recurse into sub-diretories to build sub-packages.
include(modules.cmake)

# === Create te project library.
CREATE_PROJECT_LIBRARY(pelican-astro)
if(BUILD_SINGLE_LIB)
    set_target_properties(pelican-astro PROPERTIES
        COMPILE_FLAGS "${OpenMP_CXX_FLAGS}"
        LINK_FLAGS "${OpenMP_CXX_FLAGS}")
endif(BUILD_SINGLE_LIB)
