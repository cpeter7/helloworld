set(EXE_SRC "main.cpp")

add_executable(${EXE_NAME} ${EXE_SRC})

target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME} nlohmann_json)

if(${ENABLE_WARNINGS})
    target_set_warnings(${EXE_NAME} ${ENABLE_WARNINGS}
                        ${ENABLE_WARNINGS_AS_ERRORS})
endif()

if(${ENABLE_CLANG_TIDY})
    add_clang_tidy_to_target(${EXE_NAME})
endif()
