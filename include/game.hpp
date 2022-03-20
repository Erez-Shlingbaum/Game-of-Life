#pragma once

#include <cstdint>
#include <random>
#include <string>
#include <vector>

#include "cell.hpp"
#include "sdl_wrappings.hpp"
#include "renderer.hpp"
#include "screen_dimensions.hpp"
#include "window.hpp"
#include "pair_hasher.hpp"

class Game
{
public:
    Game(std::string title, size_t cell_width, size_t cell_height);
    ~Game() = default;

    void run();

private:
    static constexpr uint8_t MIN_BLUE_STRENGTH = 64;

    using CellTimeAliveTrackerMap = std::unordered_map<std::pair<size_t, size_t>, uint8_t, PairHasher>;
    static CellTimeAliveTrackerMap create_initialized_map(size_t rows, size_t cols);
    void init_cells();
    [[nodiscard]] size_t cell_count_neighbours(size_t row, size_t col);

    bool handle_events(SDL_Event &event) const;
    void update();
    void draw();

    void update_neighbour_counts();
    void update_cells();

    void cell_draw_matrix();

    static void increment_in_range(uint8_t &byte, uint8_t amount, uint8_t min_allowed_value);
    [[nodiscard]] size_t cell_rows() const;
    [[nodiscard]] size_t cell_cols() const;

    std::string _title;
    ScreenDimensions _screen_dimensions;
    size_t _cell_width;
    size_t _cell_height;
    size_t _cell_rows;
    size_t _cell_cols;

    CountCellMatrix _neighbour_counts;
    CellStateMatrix _cells;
    CellTimeAliveTrackerMap _cell_time_alive_tracker_map;

    SDL::Window _window;
    SDL::Renderer _renderer;
};