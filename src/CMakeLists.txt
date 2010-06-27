# === Set the project name and specify the required CMAKE version.
project(pelican-astro CXX C)
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

# === Set the project version.
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# === CMake setup.
list(INSERT CMAKE_MODULE_PATH 0 ${pelican-astro_SOURCE_DIR}/cmake)
include(cmake/packagemacrosNew.cmake)
enable_testing()


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

# === Set dependencies.
include(cmake/dependencies.cmake)

# === Set compiler options.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include(cmake/compilerDefaults.cmake)

DECLARE_PROJECT_LIBRARY(pelican-astro
    adapters
    chunkers
    data
    modules
    pipelines
)

# === Recurse into sub-diretories.
include(modules.cmake)

CREATE_PROJECT_LIBRARY(pelican-astro)


