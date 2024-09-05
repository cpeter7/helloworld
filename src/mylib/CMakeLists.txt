set(LIB_SRC "mylib.cpp")
set(LIB_HDR "mylib.h")

add_library(${LIB_NAME} STATIC ${LIB_SRC} ${LIB_HDR}) 

target_include_directories(${LIB_NAME} PUBLIC 
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")