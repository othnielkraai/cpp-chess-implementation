#pragma once

#include "domain/move/chessmove/validator/special_move_validator.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class PieceMoveValidator : public IChessMoveValidator
    {
    public:
        PieceMoveValidator(std::unique_ptr<IChessMoveValidator> validator);

        virtual bool isValidMove(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const override;

    private:
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

    private:
        std::unique_ptr<IChessMoveValidator> m_SpecialMoveValidator;
    };
}