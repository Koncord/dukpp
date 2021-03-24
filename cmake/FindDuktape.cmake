include(ExternalProject)
include(FindPackageHandleStandardArgs)
include(Common/Core)

# # Base variables
if (Duktape_FIND_VERSION)
    set(duktape_version ${Duktape_FIND_VERSION})
else ()
    set(duktape_version 2.6.0)
endif ()

set(duktape_lib duktape_lib_${duktape_version})

set(duktape_build_toplevel "${CMAKE_BINARY_DIR}/vendor/duktape_${duktape_version}")
set(duktape_include_dirs "${duktape_build_toplevel}/src")


set(duktape_sources duktape.h duktape.c duk_config.h)
prepend(duktape_sources "${duktape_build_toplevel}/src/" ${duktape_sources})

ExternalProject_Add(DUKTAPE_BUILD_SOURCE
        BUILD_IN_SOURCE TRUE
        BUILD_ALWAYS FALSE
        URL https://duktape.org/duktape-${duktape_version}.tar.xz
        TLS_VERIFY TRUE
        PREFIX ${duktape_build_toplevel}
        SOURCE_DIR ${duktape_build_toplevel}
        DOWNLOAD_DIR ${duktape_build_toplevel}
        TMP_DIR "${duktape_build_toplevel}-tmp"
        STAMP_DIR "${duktape_build_toplevel}-stamp"
        INSTALL_DIR "${duktape_build_toplevel}/local"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        BUILD_BYPRODUCTS "${duktape_sources}")

add_library(${duktape_lib} INTERFACE)
target_include_directories(${duktape_lib} INTERFACE ${duktape_include_dirs})
target_sources(${duktape_lib} INTERFACE "${duktape_build_toplevel}/src/duktape.c")
add_dependencies(${duktape_lib} DUKTAPE_BUILD_SOURCE)

set(DUKTAPE_FOUND TRUE)
set(DUKTAPE_LIBRARIES ${duktape_lib})
set(DUKTAPE_INCLUDE_DIRS ${duktape_include_dirs})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(Duktape
        FOUND_VAR DUKTAPE_FOUND
        REQUIRED_VARS DUKTAPE_LIBRARIES DUKTAPE_INCLUDE_DIRS
        VERSION_VAR duktape_version)