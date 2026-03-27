#include "domain/move/chessmove/validator/king_safety_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

#include <cmath>
#include <memory>

namespace boardgame::move::chess
{
    bool KingSafetyValidator::isValidMove(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        return !leavesKingInCheck(board, move);
    }

    bool KingSafetyValidator::leavesKingInCheck(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        auto* sourcePiece = board.getPieceAt(move.getFrom());
        if (sourcePiece == nullptr)
        {
            return true;
        }

        const auto color = sourcePiece->getColor();

        std::unique_ptr<boardgame::board::chess::IChessBoard> clonedBoard = board.clone();
        if (!clonedBoard)
        {
            return true;
        }

        if (!simulateMoveOnBoard(*clonedBoard, move))
        {
            return true;
        }

        return isKingInCheck(*clonedBoard, color);
    }

    bool KingSafetyValidator::simulateMoveOnBoard(
        boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        switch (move.getMoveType())
        {
        case ChessMoveType::Normal:
        case ChessMoveType::PawnDoubleMove:
        case ChessMoveType::Promotion:
            return board.movePiece(from, to);

        case ChessMoveType::EnPassant:
        {
            if (!board.movePiece(from, to))
            {
                return false;
            }

            boardgame::core::Position capturedPawnPos{from.row, to.col};
            return board.removePiece(capturedPawnPos);
        }

        case ChessMoveType::Castling:
        {
            if (!board.movePiece(from, to))
            {
                return false;
            }

            const bool kingSide = to.col > from.col;
            const int rookFromCol = kingSide ? 7 : 0;
            const int rookToCol = kingSide ? to.col - 1 : to.col + 1;

            boardgame::core::Position rookFrom{from.row, rookFromCol};
            boardgame::core::Position rookTo{from.row, rookToCol};

            return board.movePiece(rookFrom, rookTo);
        }

        default:
            return false;
        }
    }

    bool KingSafetyValidator::isKingInCheck(
        const boardgame::board::chess::IChessBoard& board,
        boardgame::piece::chess::ChessPieceColor color
    ) const
    {
        const boardgame::core::Position kingPos = board.findKing(color);
        return isSquareAttacked(board, kingPos, utils::oppositeColor(color));
    }

    bool KingSafetyValidator::isSquareAttacked(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& square,
        boardgame::piece::chess::ChessPieceColor attackingColor
    ) const
    {
        const auto pieces = board.getPieces(attackingColor);

        for (const auto& [pos, piece] : pieces)
        {
            if (piece == nullptr)
            {
                continue;
            }

            if (canPieceAttackSquare(board, pos, *piece, square))
            {
                return true;
            }
        }

        return false;
    }

    bool KingSafetyValidator::canPieceAttackSquare(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& from,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& target
    ) const
    {
        using boardgame::piece::chess::ChessPieceType;

        const int dRow = target.row - from.row;
        const int dCol = target.col - from.col;

        switch (piece.getType())
        {
        case ChessPieceType::Pawn:
        {
            const int forward = utils::pawnForwardDirection(piece.getColor());
            return dRow == forward && std::abs(dCol) == 1;
        }

        case ChessPieceType::Knight:
        {
            return (std::abs(dRow) == 2 && std::abs(dCol) == 1) ||
                   (std::abs(dRow) == 1 && std::abs(dCol) == 2);
        }

        case ChessPieceType::Bishop:
        {
            if (std::abs(dRow) != std::abs(dCol))
            {
                return false;
            }

            return utils::isPathClear(board, from, target);
        }

        case ChessPieceType::Rook:
        {
            const bool straight =
                (dRow == 0 && dCol != 0) ||
                (dCol == 0 && dRow != 0);

            if (!straight)
            {
                return false;
            }

            return utils::isPathClear(board, from, target);
        }

        case ChessPieceType::Queen:
        {
            const bool diagonal = std::abs(dRow) == std::abs(dCol);
            const bool straight =
                (dRow == 0 && dCol != 0) ||
                (dCol == 0 && dRow != 0);

            if (!(diagonal || straight))
            {
                return false;
            }

            return utils::isPathClear(board, from, target);
        }

        case ChessPieceType::King:
        {
            return std::abs(dRow) <= 1 && std::abs(dCol) <= 1;
        }

        default:
            return false;
        }
    }
}