set(LIB_SRC "mylib.cpp")
set(LIB_HDR "mylib.h")
set(LIB_INCLUDES "./" "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${LIB_NAME} STATIC ${LIB_SRC} ${LIB_HDR})

target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDES})

target_link_libraries(
    ${LIB_NAME}
    PUBLIC nlohmann_json::nlohmann_json
           fmt::fmt
           spdlog::spdlog
           cxxopts::cxxopts)

if(${ENABLE_WARNINGS})
    # message(STATUS "${LIB_NAME} ${ENABLE_WARNINGS} ${ENABLE_WARNINGS_AS_ERRORS}")
    target_set_warnings(${LIB_NAME} ${ENABLE_WARNINGS}
                        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_LTO})
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        message(STATUS "IPO/LTO is supported!")
        set_property(TARGET ${LIB_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION
                                                 ON)
    else()
        message(WARNING "IPO/LTO is not supported!")
    endif()
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${LIB_NAME})
endif()
