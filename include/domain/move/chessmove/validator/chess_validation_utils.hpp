#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

namespace boardgame::move::chess::utils
{
    bool isOccupied(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& pos
    );

    bool isOccupiedByEnemy(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& pos,
        boardgame::piece::chess::ChessPieceColor myColor
    );

    bool isOccupiedByOwnColor(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& pos,
        boardgame::piece::chess::ChessPieceColor myColor
    );

    bool isDestinationOccupiedByOwnPiece(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    );

    int rowDelta(const boardgame::move::chess::IChessMove& move);
    int colDelta(const boardgame::move::chess::IChessMove& move);
    int getStep(int delta);

    bool isPathClear(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& from,
        const boardgame::core::Position& to
    );

    int pawnForwardDirection(boardgame::piece::chess::ChessPieceColor color);
    int pawnStartRow(boardgame::piece::chess::ChessPieceColor color);
    int promotionRow(boardgame::piece::chess::ChessPieceColor color);

    boardgame::piece::chess::ChessPieceColor oppositeColor(
        boardgame::piece::chess::ChessPieceColor color
    );
}