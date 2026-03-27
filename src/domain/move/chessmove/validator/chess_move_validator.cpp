#include "domain/move/chessmove/validator/chess_move_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

namespace boardgame::move::chess
{
    bool ChessMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        for (const auto& validator : validators)
        {
            if (!validator->isValidMove(board, move))
            {
                return false;
            }
        }

        return true;
        
        // if (!m_BasicMoveValidator.isValidMove(board, move))
        // {
        //     return false;
        // }

        // if (!m_PieceMoveValidator.isValidMove(board, move))
        // {
        //     return false;
        // }

        // if (m_KingSafetyValidator.leavesKingInCheck(board, move))
        // {
        //     return false;
        // }

        // const auto* piece = board.getPieceAt(move.getFrom());
        // if (piece != nullptr &&
        //     piece->getType() == boardgame::piece::chess::ChessPieceType::King &&
        //     move.getMoveType() == ChessMoveType::Castling)
        // {
        //     if (m_KingSafetyValidator.isKingInCheck(board, piece->getColor()))
        //     {
        //         return false;
        //     }

        //     const auto from = move.getFrom();
        //     const auto to = move.getTo();
        //     const int step = (to.col > from.col) ? 1 : -1;

        //     boardgame::core::Position through{from.row, from.col + step};
        //     boardgame::core::Position destination{from.row, from.col + 2 * step};

        //     const auto enemyColor = boardgame::move::chess::utils::oppositeColor(piece->getColor());

        //     if (m_KingSafetyValidator.isSquareAttacked(board, through, enemyColor))
        //     {
        //         return false;
        //     }

        //     if (m_KingSafetyValidator.isSquareAttacked(board, destination, enemyColor))
        //     {
        //         return false;
        //     }
        // }
    }
}