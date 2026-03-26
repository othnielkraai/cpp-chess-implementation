#include "domain/move/chessmove/chess_move_validator.hpp"

namespace boardgame::move::chess
{
    bool ChessMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move
    ) const
    {
        // TODO later:
        // - simulate move
        // - check king safety
        // - check rules

        return true; // tijdelijk alles toestaan
    }
}