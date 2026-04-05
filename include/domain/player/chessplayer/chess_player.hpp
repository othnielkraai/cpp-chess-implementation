#pragma once

// Interfaces
#include "interfaces/player/chessplayer/IChessPlayer.hpp"

namespace boardgame::player::chess
{
    class ChessPlayer : public IChessPlayer
    {
    public:
        ChessPlayer(bool isWhite);

        virtual bool isWhite() const override;

    private:
        bool m_IsWhite;
    };
}