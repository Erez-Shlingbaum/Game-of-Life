#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>
#include "cell.hpp"
#include "sdl_wrappings.hpp"
#include "../src/renderer.hpp"

class Game
{
public:
    Game(std::string title, size_t screen_width, size_t screen_height, size_t cell_width, size_t cell_height);
    ~Game() = default;

    void run();

private:
    void init_cells();

    [[nodiscard]] inline bool is_valid_position(size_t row, size_t col) const;
    [[nodiscard]] size_t cell_count_neighbours(size_t row, size_t col);

    bool handle_events(SDL_Event &event) const;
    void update();
    void draw();

    void update_neighbour_counts();
    void update_cells();

    void cell_draw_matrix();

    [[nodiscard]] size_t cell_rows() const;
    [[nodiscard]] size_t cell_cols() const;

    std::string _title;
    size_t _screen_width;
    size_t _screen_height;

    size_t _cell_width;
    size_t _cell_height;
    size_t _cell_rows;
    size_t _cell_cols;

    CountCellMatrix _neighbour_counts;
    CellStateMatrix _cells;

    SDL::ManagedWindow _window;
    Renderer _renderer;
};