cmake_minimum_required(VERSION 3.22)

option(ENABLE_WARNINGS "Enable warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable warnings as erros" OFF)

option(ENABLE_TESTING "Enable a Unit Testing Build" ON)
option(ENABLE_COVERAGE "Enable a Code Coverage build" ON)

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitizer" ON)
option(ENABLE_SANITIZE_UNDEFINED "Enable Address Sanitizer" ON)

option(ENABLE_LTO "Enable to add link time optimization" ON)

option(USE_CPM "Using CPM" ON)

option(ENABLE_CLANG_TIDY "Enable to add clang tidy." ON)
# option(USES_TERMINAL "use terminal" ON)

option(ENABLE_CLANG_FORMAT "Enable to add clang-format" ON)
option(ENABLE_CMAKE_FORMAT "Enable to add cmake-format" ON)

# set(ENABLE_WARNINGS_AS_ERRORS OFF)
#message(STATUS, "ENABLE_TESTING: ${ENABLE_TESTING} ENABLE_WARNINGS: ${ENABLE_WARNINGS} ENABLE_WARNINGS_AS_ERRORS: ${ENABLE_WARNINGS_AS_ERRORS}")
set(LIB_NAME "mylib")
set(EXE_NAME "helloworld")

project(
    ${EXE_NAME}
    VERSION 1.0.0
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)
include(FetchContent)
include(Docs)
include(Tools)

if(ENABLE_WARNINGS)
    include(Warnings)
    message(STATUS "enable_warnings")
endif()

if(ENABLE_SANITIZE_ADDR OR ENABLE_SANITIZE_UNDEFINED)
    add_compile_options("-fno-omit-frame-pointer")
    add_link_options("-fno-omit-frame-pointer")

    if(ENABLE_SANITIZE_ADDR)
        add_compile_options("-fsanitize=address")
        add_link_options("-fsanitize=address")
    endif()

    if(ENABLE_SANITIZE_UNDEFINED)
        add_compile_options("-fsanitize=undefined")
        add_link_options("-fsanitize=undefined")
    endif()
endif()

if (ENABLE_TESTING AND ENABLE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

if(ENABLE_LTO)
    include(LTO)
endif()

if(USE_CPM)
    message(STATUS "Using CPM")
    include(CPM)
    cpmaddpackage("gh:nlohmann/json#v3.11.3")
    cpmaddpackage("gh:fmtlib/fmt#9.1.0")
    cpmaddpackage("gh:gabime/spdlog#v1.11.0")
    cpmaddpackage("gh:jarro2783/cxxopts#v3.1.1")
    if(ENABLE_TESTING)
        cpmaddpackage("gh:catchorg/Catch2#v3.5.3")
        list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    endif()
else()
    # add_git_submodule(external/json)
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(nlohmann_json)

    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 9.1.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(fmt)

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG v1.11.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(spdlog)

    FetchContent_Declare(
        cxxopts
        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
        GIT_TAG v3.0.0
        GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(cxxopts)

    if(ENABLE_TESTING)
        FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2
            GIT_TAG v3.5.3
            GIT_SHALLOW TRUE)
        FetchContent_MakeAvailable(Catch2)
        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    endif()
endif()

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)

if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

if(${ENABLE_CLANG_FORMAT})
    add_clang_format_target()
endif()

if(${ENABLE_CMAKE_FORMAT})
    add_cmake_format_target()
endif()
