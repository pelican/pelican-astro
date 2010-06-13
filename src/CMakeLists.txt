# === Set the project name and specify the required CMAKE version.
project(pelican-astro CXX C)
cmake_minimum_required(VERSION 2.4 FATAL_ERROR)

# === Set the project version.
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# === Append the src/cmake directory to the module path.
list(INSERT CMAKE_MODULE_PATH 0 ${pelican-astro_SOURCE_DIR}/cmake)

# === Enable the cmake testing framework.
enable_testing()

# === Options and defaults.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif(NOT CMAKE_BUILD_TYPE)

if(NOT PELICAN_INSTALL_DIR)
    set(PELICAN_INSTALL_DIR "pelican")
endif(NOT PELICAN_INSTALL_DIR )

if(NOT LIBRARY_INSTALL_DIR)
    set(LIBRARY_INSTALL_DIR ${PELICAN_INSTALL_DIR}/lib)
endif(NOT LIBRARY_INSTALL_DIR)

if(NOT BINARY_INSTALL_DIR)
    set(BINARY_INSTALL_DIR ${PELICAN_INSTALL_DIR}/bin)
endif(NOT BINARY_INSTALL_DIR)

if(NOT DOC_INSTALL_DIR)
    set(DOC_INSTALL_DIR ${PELICAN_INSTALL_DIR}/doc)
endif(NOT DOC_INSTALL_DIR)

# === Set dependencies.
include(dependencies)

# === Set compiler options.
include(compilerDefaults)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# === Recurse into sub-diretories.
include(modules.cmake)

# === Build the pelican-astro library.


