file(GLOB_RECURSE BOARDGAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(BoardGameLib STATIC
    ${BOARDGAME_SOURCES}
)

target_include_directories(BoardGameLib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)