#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

namespace boardgame::move::chess::utils
{
    int rowDelta(const boardgame::move::chess::IChessMove& move)
    {
        return move.getTo().row - move.getFrom().row;
    }

    int colDelta(const boardgame::move::chess::IChessMove& move)
    {
        return move.getTo().col - move.getFrom().col;
    }

    int getStep(int delta)
    {
        if (delta > 0)
        {
            return 1;
        }

        if (delta < 0)
        {
            return -1;
        }

        return 0;
    }

    bool isPathClear(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& from,
        const boardgame::core::Position& to
    )
    {
        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;

        const int rowStep = getStep(dRow);
        const int colStep = getStep(dCol);

        int currentRow = from.row + rowStep;
        int currentCol = from.col + colStep;

        while (currentRow != to.row || currentCol != to.col)
        {
            if (board.getPieceAt({currentRow, currentCol}) != nullptr)
            {
                return false;
            }

            currentRow += rowStep;
            currentCol += colStep;
        }

        return true;
    }

    int pawnForwardDirection(boardgame::piece::chess::ChessPieceColor color)
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? -1 : 1;
    }

    int pawnStartRow(boardgame::piece::chess::ChessPieceColor color)
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? 6 : 1;
    }

    int promotionRow(boardgame::piece::chess::ChessPieceColor color)
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? 0 : 7;
    }

    boardgame::piece::chess::ChessPieceColor oppositeColor(
        boardgame::piece::chess::ChessPieceColor color
    )
    {
        return color == boardgame::piece::chess::ChessPieceColor::White
            ? boardgame::piece::chess::ChessPieceColor::Black
            : boardgame::piece::chess::ChessPieceColor::White;
    }
}