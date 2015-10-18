project(test)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
AUX_SOURCE_DIRECTORY(../mtcp SRCS)
add_executable(test_mtcp_server mtcp_server.c ${SRCS})
target_link_libraries(test_mtcp_server event)

