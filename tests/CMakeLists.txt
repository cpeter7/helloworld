include(Catch)

add_executable("unittest_foo" "test_foo.cpp")
target_link_libraries("unittest_foo" PUBLIC "LibFoo")
target_link_libraries("unittest_foo" PRIVATE "LibFoo" Catch2::Catch2WithMain)

add_executable("unittest_bar" "test_bar.cpp")
target_link_libraries("unittest_bar" PUBLIC "LibBar")
target_link_libraries("unittest_bar" PRIVATE "LibBar" Catch2::Catch2WithMain)

if(${ENABLE_WARNINGS})
    target_set_warnings(
        TARGET
        "unittest_foo"
        ENABLE
        ON
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS} )
    target_set_warnings(
        TARGET
        "unittest_bar"
        ENABLE
        ON
        AS_ERRORS
        ${ENABLE_WARNINGS_AS_ERRORS} )
endif()

catch_discover_tests("unittest_foo")
catch_discover_tests("unittest_bar")

if(ENABLE_COVERAGE)
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${PROJECT_SOURCE_DIR}/app/*"
        "${PROJECT_SOURCE_DIR}/cmake/*"
        "${PROJECT_SOURCE_DIR}/docs/*"
        "${PROJECT_SOURCE_DIR}/external/*"
        "${PROJECT_SOURCE_DIR}/tests/*"
        "${PROJECT_SOURCE_DIR}/build/*"
        "/usr/include/*")
    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES "unittest_bar" "unittest_foo")

    setup_target_for_coverage_gcovr_html(
        NAME
        ${COVERAGE_MAIN}
        EXECUTABLE
        ctest
        DEPENDENCIES
        ${COVERAGE_DEPENDENCIES}
        BASE_DIRECTORY
        ${CMAKE_SOURCE_DIR})
endif()
