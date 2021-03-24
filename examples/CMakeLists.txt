file(GLOB EXAMPLES_SRC *.cpp)
source_group(examples FILES ${EXAMPLES_SRC})

function(MAKE_EXAMPLE example_source_file example_suffix target_dukpp)

    get_filename_component(example_name ${example_source_file} NAME_WE)
    file(RELATIVE_PATH example_source_file_relative ${CMAKE_SOURCE_DIR} ${example_source_file})
    get_filename_component(example_output_relative_dir ${example_source_file_relative} DIRECTORY)
    file(TO_CMAKE_PATH "${example_output_relative_dir}" example_output_relative_dir_name)
    STRING(REGEX REPLACE "/" "." example_output_relative_dir_name "${example_output_relative_dir}")
    set(example_name "${example_name}${example_suffix}")
    if (example_output_relative_dir_name STREQUAL "")
        set(example_output_name "${example_name}")
    else ()
        set(example_output_name "${example_output_relative_dir_name}.${example_name}")
    endif ()

    add_executable(${example_name} ${example_source_file})
    set_target_properties(${example_name}
            PROPERTIES
            OUTPUT_NAME "${example_output_name}"
            EXPORT_NAME dukpp::${example_output_name})

    if (MSVC)
        target_compile_options(${example_name}
                PRIVATE $<$<COMPILE_LANGUAGE:CXX>:/std:c++17> /EHsc /W4)
        target_compile_definitions(${example_name}
                PRIVATE UNICODE _UNICODE
                _CRT_SECURE_NO_WARNINGS _CRT_SECURE_NO_DEPRECATE)
    else ()
        target_compile_options(${example_name}
                PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-std=c++1z
                -ftemplate-backtrace-limit=0>
                -Wno-unknown-warning -Wno-unknown-warning-option -Wno-unused-value
                -Wall -Wpedantic -Werror -pedantic -pedantic-errors
                $<$<COMPILE_LANGUAGE:CXX>:-Wno-noexcept-type -Wno-unused-local-typedefs>)
    endif ()

    target_link_libraries(${example_name} PRIVATE Threads::Threads ${target_dukpp} ${DUKTAPE_LIBRARIES})

    if (DUKPP_TESTS_EXAMPLES)
        add_test(NAME ${example_output_name} COMMAND ${example_name})
    endif ()
    if (DUKPP_ENABLE_INSTALL)
        install(TARGETS ${example_name} RUNTIME DESTINATION bin)
    endif ()
endfunction(MAKE_EXAMPLE)

if (DUKPP_ENABLE_EXAMPLES)
    foreach (example_source_file ${EXAMPLES_SRC})
        MAKE_EXAMPLE(${example_source_file} "" dukpp::dukpp)
    endforeach ()
endif ()
