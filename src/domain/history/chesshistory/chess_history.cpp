#include <vector>
#include <memory>

#include "domain/history/chesshistory/chess_histroy.hpp"

namespace boardgame::history::chess
{
    void ChessHistory::addRecord(std::unique_ptr<ChessRecord> record)
    {
        m_records.push_back(std::move(record));
    }

    std::vector<std::unique_ptr<ChessRecord>>& ChessHistory::getHistory()
    {
        return m_records;
    }

    std::optional<std::unique_ptr<ChessRecord>> ChessHistory::undo()
    {
        if (m_records.empty())
        {
            return std::nullopt;
        }

        auto lastRecord = std::move(m_records.back());
        m_records.pop_back();

        return std::make_optional(std::move(lastRecord));
    }
    
    std::optional<std::unique_ptr<ChessRecord>> ChessHistory::redo()
    {
        if (m_undoneRecords.empty())
        {
            return std::nullopt;
        }

        auto lastUndoneRecord = std::move(m_undoneRecords.back());
        m_undoneRecords.pop_back();

        m_records.push_back(std::move(lastUndoneRecord));

        return std::make_optional(std::move(m_records.back()));
    }
}