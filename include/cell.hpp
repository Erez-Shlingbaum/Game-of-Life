#pragma once

#include <SDL.h>
#include <vector>

// TODO: get this at runtime
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

constexpr auto CELL_WIDTH = 5;
constexpr auto CELL_HEIGHT = 5;

enum class CellState
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