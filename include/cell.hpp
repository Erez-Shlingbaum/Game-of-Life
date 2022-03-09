#pragma once

#include <SDL.h>
#include <vector>


enum class CellState : uint8_t
{
    DEAD, ALIVE
};

struct CountCell
{
    CellState cell;
    size_t count;
};


using CellStateMatrix = std::vector<std::vector<CellState>>;
using CountCellMatrix = std::vector<std::vector<CountCell>>;