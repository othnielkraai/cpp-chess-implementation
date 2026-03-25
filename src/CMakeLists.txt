add_library(BoardGameLib INTERFACE)

target_include_directories(BoardGameLib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)