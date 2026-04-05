add_executable(Run-Chess-API main.cpp)

target_link_libraries(Run-Chess-API
    PRIVATE
        ChessGameLib
)