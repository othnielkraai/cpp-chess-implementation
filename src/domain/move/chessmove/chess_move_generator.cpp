#include "domain/move/chessmove/chess_move_generator.hpp"

namespace boardgame::move::chess
{
    ChessMoveGenerator::ChessMoveGenerator(std::unique_ptr<IChessMoveValidator> moveValidator)
        : m_MoveValidator(std::move(moveValidator))
    {
    }

    std::vector<std::unique_ptr<IChessMove>> ChessMoveGenerator::generateMoves(
        const boardgame::board::chess::IChessBoard &board) const
    {
        std::vector<std::unique_ptr<IChessMove>> moves;

        for (const auto &[pos, piece] : board.getPieces())
        {
            if (!piece)
            {
                continue;
            }

            auto pieceMoves = generateMoves(board, pos);

            for (auto &move : pieceMoves)
            {
                moves.push_back(std::move(move));
            }
        }

        return moves;
    }

    std::vector<std::unique_ptr<IChessMove>> ChessMoveGenerator::generateMoves(const boardgame::board::chess::IChessBoard &board, const Position &from) const
    {
        std::vector<std::unique_ptr<IChessMove>> moves;

        auto piece = board.getPieceAt(from);

        if (!piece)
        {
            return moves;
        }

        auto pieceMoves = piece->getMoveStrategy()->generateMoves(board, *piece, from);

        for (auto &move : pieceMoves)
        {
            if (m_MoveValidator->isValidMove(board, *move))
            {
                moves.push_back(std::move(move));
            }
        }

        return moves;
    }
}