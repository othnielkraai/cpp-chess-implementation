#include "domain/player/chessplayer/chess_player.hpp"

namespace boardgame::player::chess
{
    ChessPlayer::ChessPlayer(bool isWhite) : m_IsWhite(isWhite)
    {
    }

    bool ChessPlayer::isWhite() const
    {
        return m_IsWhite;
    }
}