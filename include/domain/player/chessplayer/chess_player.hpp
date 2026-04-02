#pragma once

// Interfaces
#include "interfaces/player/chessplayer/IChessPlayer.hpp"

namespace boardgame::player::chess
{
    class ChessPlayer : public IChessPlayer
    {
    public:
        // Constructor takes a boolean indicating if the player is playing as white (true) or black (false)
        ChessPlayer(bool isWhite);

        virtual bool isWhite() const override;

    private:
        bool m_IsWhite;
    };
}