set(LIB_SOURCES
    lib.cpp
)

set(LIB_HEADERS
    lib.h
)

set(LIB_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR} 
)

add_library(${LIB_NAME} STATIC ${LIB_SOURCES} ${LIB_HEADERS})

target_include_directories(${LIB_NAME} PUBLIC ${LIB_INCLUDES})

