#pragma once

#include <vector>

namespace boardgame::move
{
    class IMoveGenerator
    {
    public:
        virtual ~IMoveGenerator() = default;
    };
}