#pragma once

#include <vector>
#include <memory>

#include "domain/history/chesshistory/chess_histroy.hpp"

namespace boardgame::history::chess
{
    void ChessHistory::addRecord(std::unique_ptr<ChessRecord> record)
    {
        m_records.push_back(std::move(record));
    }

    const std::vector<std::unique_ptr<ChessRecord>>& ChessHistory::getHistory() const
    {
        return m_records;
    }
}