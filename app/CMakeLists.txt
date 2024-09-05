set(EXE_SRC "main.cpp")

add_executable(${EXE_NAME} ${EXE_SRC})

target_link_libraries(${EXE_NAME} PRIVATE 
    ${LIB_NAME}
    nlohmann_json)
