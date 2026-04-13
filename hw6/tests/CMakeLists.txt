add_executable(PoolTest test.cpp)

target_link_libraries(PoolTest PoolImpl)

target_include_directories(PoolTest PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME Test COMMAND PoolTest)
