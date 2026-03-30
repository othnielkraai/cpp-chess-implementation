#pragma once

#include <tuple>

namespace boardgame::core{
    struct Position{
        int row;
        int col;

        /// @brief Compares this position with another position.
        /// @param other The position to compare with.
        /// @return True if this position is less than the other position, false otherwise.
        bool operator<(const Position& other) const {
            return std::tie(row, col) < std::tie(other.row, other.col);
        }

        /// @brief Checks if this position is equal to another position.
        /// @param other The position to compare with.
        /// @return True if the positions are equal, false otherwise.
        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }

        /// @brief Checks if this position is not equal to another position.
        /// @param other The position to compare with.
        /// @return True if the positions are not equal, false otherwise.
        bool operator!=(const Position& other) const {
            return !(*this == other);
        }
    };
}