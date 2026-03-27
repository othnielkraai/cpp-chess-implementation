#pragma once

#include <tuple>

namespace boardgame::core{
    struct Position{
        int row;
        int col;

        bool operator<(const Position& other) const {
            return std::tie(row, col) < std::tie(other.row, other.col);
        }

        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }

        bool operator!=(const Position& other) const {
            return !(*this == other);
        }
    };
}