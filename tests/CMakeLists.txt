include(Catch)

add_executable("unittest_foo" "test_foo.cpp")
target_link_libraries("unittest_foo" PUBLIC ${LIB_NAME} Catch2::Catch2WithMain)

catch_discover_tests("unittest_foo")
