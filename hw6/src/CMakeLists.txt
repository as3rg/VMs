set(SOURCES
    pool.cpp
)

set(HEADERS
    pool.h
)

add_library(PoolImpl STATIC ${SOURCES} ${HEADERS})

target_include_directories(PoolImpl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
