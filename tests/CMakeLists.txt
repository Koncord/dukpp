find_package(Catch REQUIRED)

include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/include)

file(GLOB TEST_SOURCES *.cpp)

if (DUKPP_ENABLE_TESTS)
    add_executable(tests ${TEST_SOURCES})
    target_link_libraries(tests PUBLIC Threads::Threads ${DUKTAPE_LIBRARIES} ${CATCH_LIBRARIES})
endif ()
