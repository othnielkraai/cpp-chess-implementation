add_executable(BoardGame_demo main.cpp)

target_link_libraries(BoardGame_demo
    PRIVATE
        BoardGameLib
)