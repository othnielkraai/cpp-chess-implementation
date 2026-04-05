file(GLOB_RECURSE BOARDGAME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_library(ChessGameLib STATIC
    ${BOARDGAME_SOURCES}
)

target_include_directories(ChessGameLib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)