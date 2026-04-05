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


        virtual std::vector<std::unique_ptr<ChessRecord>>& getHistory() override;

        virtual std::optional<std::unique_ptr<ChessRecord>> undo() override;

        virtual std::optional<std::unique_ptr<ChessRecord>> redo() override;

    private:
        std::vector<std::unique_ptr<ChessRecord>> m_records;
        std::vector<std::unique_ptr<ChessRecord>> m_undoneRecords;
    };
}