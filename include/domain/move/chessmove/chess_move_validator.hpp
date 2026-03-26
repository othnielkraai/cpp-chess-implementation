#pragma once

#include "interfaces/move/chessmove/IChessMoveValidator.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "core/common/position.hpp"

#include <memory>

namespace boardgame::move::chess
{
    class ChessMoveValidator : public IChessMoveValidator
    {
    public:
        bool isValidMove(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const override;

    private:
        bool isBasicMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isMoveShapeValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& piece
        ) const;

        bool isPawnMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& piece
        ) const;

        bool isKnightMoveValid(
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isBishopMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isRookMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isQueenMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isKingMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& piece
        ) const;

        bool isCastlingMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& king
        ) const;

        bool isEnPassantMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& pawn
        ) const;

        bool isPromotionMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& pawn
        ) const;

        bool leavesKingInCheck(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool simulateMoveOnBoard(
            boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isKingInCheck(
            const boardgame::board::chess::IChessBoard& board,
            boardgame::piece::chess::ChessPieceColor color
        ) const;

        bool isSquareAttacked(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& square,
            boardgame::piece::chess::ChessPieceColor attackingColor
        ) const;

        bool canPieceAttackSquare(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& from,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& target
        ) const;

        bool isPathClear(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& from,
            const boardgame::core::Position& to
        ) const;

        bool isDestinationOccupiedByOwnPiece(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isOccupied(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& pos
        ) const;

        bool isOccupiedByEnemy(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& pos,
            boardgame::piece::chess::ChessPieceColor myColor
        ) const;

        bool isOccupiedByOwnColor(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& pos,
            boardgame::piece::chess::ChessPieceColor myColor
        ) const;

        int rowDelta(const boardgame::move::chess::IChessMove& move) const;
        int colDelta(const boardgame::move::chess::IChessMove& move) const;
        int getStep(int delta) const;

        int pawnForwardDirection(boardgame::piece::chess::ChessPieceColor color) const;
        int pawnStartRow(boardgame::piece::chess::ChessPieceColor color) const;
        int promotionRow(boardgame::piece::chess::ChessPieceColor color) const;

        boardgame::piece::chess::ChessPieceColor oppositeColor(
            boardgame::piece::chess::ChessPieceColor color
        ) const;
    };
}