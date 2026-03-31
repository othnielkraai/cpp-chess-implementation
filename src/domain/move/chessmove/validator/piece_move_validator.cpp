#include "domain/move/chessmove/validator/piece_move_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

#include <cmath>

namespace boardgame::move::chess
{
    PieceMoveValidator::PieceMoveValidator(std::unique_ptr<IChessMoveValidator> validator): m_SpecialMoveValidator{std::move(validator)}{}

    bool PieceMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        auto* piece = board.getPieceAt(move.getFrom());
        if (piece == nullptr)
        {
            return false;
        }

        return isMoveShapeValid(board, move, *piece);
    }

    bool PieceMoveValidator::isMoveShapeValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move,
        const boardgame::piece::chess::IChessPiece& piece
    ) const
    {
        using boardgame::piece::chess::ChessPieceType;

        switch (piece.getType())
        {
        case ChessPieceType::Pawn:
            return isPawnMoveValid(board, move, piece);

        case ChessPieceType::Knight:
            return isKnightMoveValid(move);

        case ChessPieceType::Bishop:
            return isBishopMoveValid(board, move);

        case ChessPieceType::Rook:
            return isRookMoveValid(board, move);

        case ChessPieceType::Queen:
            return isQueenMoveValid(board, move);

        case ChessPieceType::King:
            return isKingMoveValid(board, move, piece);

        default:
            return false;
        }
    }

    bool PieceMoveValidator::isPawnMoveValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move,
        const boardgame::piece::chess::IChessPiece& piece
    ) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;
        const int forward = utils::pawnForwardDirection(piece.getColor());

        switch (move.getMoveType())
        {
        case ChessMoveType::Normal:
        {
            const bool oneForward =
                (dCol == 0 && dRow == forward && board.isEmpty(to));

            const bool diagonalCapture =
                (std::abs(dCol) == 1 &&
                 dRow == forward &&
                 board.hasEnemyPiece(to, piece.getColor()));

            if (!(oneForward || diagonalCapture))
            {
                return false;
            }

            if (to.row == utils::promotionRow(piece.getColor()))
            {
                return false;
            }

            return true;
        }

        default:
           return m_SpecialMoveValidator->isValidMove(board, move);
        }
    }

    bool PieceMoveValidator::isKnightMoveValid(
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        const int dRow = std::abs(utils::rowDelta(move));
        const int dCol = std::abs(utils::colDelta(move));

        return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
    }

    bool PieceMoveValidator::isBishopMoveValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        const int dRow = std::abs(utils::rowDelta(move));
        const int dCol = std::abs(utils::colDelta(move));

        if (dRow != dCol)
        {
            return false;
        }

        return utils::isPathClear(board, move.getFrom(), move.getTo());
    }

    bool PieceMoveValidator::isRookMoveValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        const int dRow = std::abs(utils::rowDelta(move));
        const int dCol = std::abs(utils::colDelta(move));

        if (!((dRow == 0 && dCol > 0) || (dCol == 0 && dRow > 0)))
        {
            return false;
        }

        return utils::isPathClear(board, move.getFrom(), move.getTo());
    }

    bool PieceMoveValidator::isQueenMoveValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        const int dRow = std::abs(utils::rowDelta(move));
        const int dCol = std::abs(utils::colDelta(move));

        const bool diagonal = (dRow == dCol);
        const bool straight = (dRow == 0 && dCol > 0) || (dCol == 0 && dRow > 0);

        if (!(diagonal || straight))
        {
            return false;
        }

        return utils::isPathClear(board, move.getFrom(), move.getTo());
    }

    bool PieceMoveValidator::isKingMoveValid(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move,
        const boardgame::piece::chess::IChessPiece& piece
    ) const
    {
        const int dRow = std::abs(utils::rowDelta(move));
        const int dCol = std::abs(utils::colDelta(move));

        if (move.getMoveType() == ChessMoveType::Castling)
        {
            return m_SpecialMoveValidator->isValidMove(board, move);
        }

        if (move.getMoveType() != ChessMoveType::Normal)
        {
            return false;
        }

        return dRow <= 1 && dCol <= 1;
    }
}