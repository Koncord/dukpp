cmake_minimum_required(VERSION 3.15)
project(dukpp VERSION 1.0.0)

option(DUKPP_ENABLE_TESTS "Enable unit tests" ON)
option(DUKPP_ENABLE_EXAMPLES "Enable examples" ON)
option(DUKPP_ENABLE_INSTALL "Enable installation" ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
find_package(Duktape REQUIRED)
find_package(Threads REQUIRED)
include(CMakePackageConfigHelpers)

configure_package_config_file(
        cmake/dukpp-config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/dukpp-config.cmake"
        INSTALL_DESTINATION lib/cmake/dukpp
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/dukpp-config-version.cmake"
        COMPATIBILITY AnyNewerVersion)

file(GLOB DUKPP_HEADER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include/duk*.hpp)
source_group(dukpp FILES ${DUKPP_HEADER_SOURCES})

add_library(dukpp INTERFACE)
add_library(dukpp::dukpp ALIAS dukpp)
target_sources(dukpp INTERFACE ${DUKPP_SINGLE_HEADER_SOURCES})
set_target_properties(dukpp
        PROPERTIES
        EXPORT_NAME dukpp::dukpp)

target_include_directories(dukpp INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_link_libraries(dukpp INTERFACE ${DUKTAPE_LIBRARIES})

if (DUKPP_ENABLE_INSTALL)
    install(TARGETS dukpp
            EXPORT dukpp)

    install(EXPORT dukpp
            FILE dukpp-targets.cmake
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dukpp")

    install(DIRECTORY include/dukpp
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/cmake/dukpp-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake/dukpp-config-version.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/dukpp")
endif ()

if (DUKPP_ENABLE_INSTALL)
    # pkg-config support, except on Windows
    if (NOT WIN32 OR NOT CMAKE_HOST_SYSTEM_NAME MATCHES Windows)
        set(PKGCONFIG_INSTALL_DIR
                "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig"
                CACHE PATH "Path where duk.pc is installed")

        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/duk.pc.in" "${CMAKE_CURRENT_BINARY_DIR}/duk.pc" @ONLY)
        install(FILES "${CMAKE_CURRENT_BINARY_DIR}/duk.pc" DESTINATION "${PKGCONFIG_INSTALL_DIR}")
    endif ()
endif ()

if (DUKPP_ENABLE_EXAMPLES)
    message(STATUS "dukpp adding examples...")
    add_subdirectory(examples)
endif()

if (DUKPP_ENABLE_TESTS)
    message(STATUS "dukpp adding tests...")
    add_subdirectory(tests)
endif ()
