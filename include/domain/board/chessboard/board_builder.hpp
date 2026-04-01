#pragma once

#include <memory>

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "core/common/position.hpp"

namespace boardgame::board::chess
{
    class BoardBuilder
    {
    public:
        BoardBuilder& buildEmptyBoard();

        BoardBuilder& buildDefaultBoard();

        BoardBuilder& withPiece(
            const boardgame::core::Position& position,
            std::unique_ptr<boardgame::piece::chess::IChessPiece> piece
        );

        std::unique_ptr<IChessBoard> build();

    private:
        std::unique_ptr<IChessBoard> board_;
    };
}