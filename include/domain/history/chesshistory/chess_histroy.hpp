#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/history/chesshistory/IChessHistory.hpp"

using boardgame::move::chess::IChessMove;
using boardgame::history::chess::IChessHistory;

namespace boardgame::history::chess
{
    class ChessHistory : public IChessHistory
    {
    public:
        virtual void addRecord(std::unique_ptr<ChessRecord> record) override;


        virtual const std::vector<std::unique_ptr<ChessRecord>>& getHistory() const override;

    private:
        std::vector<std::unique_ptr<ChessRecord>> m_records;
    };
}