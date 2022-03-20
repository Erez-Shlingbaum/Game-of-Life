#include <cstdint>
#include <utility>
#include <iostream>

#include <SDL.h>

#include "game.hpp"
#include "cell.hpp"
#include "constants.hpp"

Game::Game(std::string title, size_t cell_width, size_t cell_height) :
        _title(std::move(title)),
        _screen_dimensions(SDL::get_current_display_mode()),
        _cell_width(cell_width),
        _cell_height(cell_height),
        _cell_rows(cell_rows()),
        _cell_cols(cell_cols()),
        _neighbour_counts(_cell_rows, std::vector<CountCell>(_cell_cols, {CellState::DEAD, 0})),
        _cells(_cell_cols, std::vector<CellState>(_cell_cols, CellState::DEAD)),
        _cell_time_alive_tracker_map(create_initialized_map(_cell_rows, _cell_cols)),
        _window(_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                _screen_dimensions.screen_width, _screen_dimensions.screen_height,
                SDL_WINDOW_FULLSCREEN
        ),
        _renderer(_window.window(), -1, SDL_RENDERER_ACCELERATED)
{
    _window.set_window_bordered(false);
    init_cells();
}

void Game::run()
{
    SDL_Event event{};
    while (handle_events(event))
    {
        auto start_time = SDL_GetTicks64();

        update();
        draw();

        const uint32_t delta_time_ms = 1000 / Consts::FPS;
        if (delta_time_ms > SDL_GetTicks64() - start_time)
        {
            SDL_Delay(delta_time_ms);
        }
    }
}

Game::CellTimeAliveTrackerMap Game::create_initialized_map(size_t rows, size_t cols)
{
    CellTimeAliveTrackerMap result_map{};
    for (size_t row = 0; row < rows; ++row)
    {
        for (size_t col = 0; col < cols; ++col)
        {
            result_map.insert({{row, col}, MIN_BLUE_STRENGTH});
        }
    }
    return result_map;
}

void Game::init_cells()
{
    std::random_device rd{};
    std::mt19937 rand_gen{rd()};
    std::uniform_int_distribution<> uniform_distribution{0, 4};

    for (int row = 0; row < _cell_rows; ++row)
    {
        for (int col = 0; col < _cell_cols; ++col)
        {
            if (uniform_distribution(rand_gen) == 0)
            {
                _cells[row][col] = CellState::ALIVE;
            }
            else
            {
                _cells[row][col] = CellState::DEAD;
            }
        }
    }
}

size_t Game::cell_count_neighbours(size_t row, size_t col)
{
    size_t count = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (i != 0 || j != 0)
            {
                const auto neighbor_row = row + i;
                const auto neighbor_col = col + j;
                // Modular structure
                count += _cells[neighbor_row % _cell_rows][neighbor_col % _cell_cols] == CellState::ALIVE;
            }
        }
    }
    return count;
}

bool Game::handle_events(SDL_Event &event) const
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}


void Game::update()
{
    update_neighbour_counts();
    update_cells();
}

void Game::draw()
{
    _renderer.set_draw_color(Color::RGB{0, 0, 0}, 0);
    _renderer.clear();

    cell_draw_matrix();
    _renderer.present();
}

void Game::update_neighbour_counts()
{
    for (int row = 0; row < _cell_rows; ++row)
    {
        for (int col = 0; col < _cell_cols; ++col)
        {
            size_t count = cell_count_neighbours(row, col);
            _neighbour_counts[row][col].count = count;
            _neighbour_counts[row][col].cell = _cells[row][col];
        };
    }
}

void Game::update_cells()
{
    constexpr auto CHANCE_TO_SURVIVE_DEATH = 1024;

    std::random_device rd{};
    std::mt19937 rand_gen{rd()};
    std::uniform_int_distribution<> uniform_distribution{0, CHANCE_TO_SURVIVE_DEATH};

    for (int row = 0; row < _cell_rows; ++row)
    {
        for (int col = 0; col < _cell_cols; ++col)
        {
            const CellState cell = _neighbour_counts[row][col].cell;
            const auto count = _neighbour_counts[row][col].count;

            if (cell == CellState::ALIVE && (count == 2 || count == 3))
            {
                // Survive
            }
            else if (cell == CellState::DEAD && count == 3)
            {
                // New cell is born!
                _cells[row][col] = CellState::ALIVE;
            }
            else
            {
                // If cell is alive, kill it
                _cells[row][col] = CellState::DEAD;

                // But, give it a 2nd chance
                if (count > 0 && uniform_distribution(rand_gen) % CHANCE_TO_SURVIVE_DEATH == 0)
                {
                    _cells[row][col] = CellState::ALIVE;
                }
            }
        }
    }
}


void Game::cell_draw_matrix()
{
    SDL_Rect rect{0, 0, Consts::CELL_WIDTH, Consts::CELL_HEIGHT};

    for (int row = 0; row < _cell_rows; ++row)
    {
        for (int col = 0; col < _cell_cols; ++col)
        {
            rect.x = col * Consts::CELL_WIDTH;
            rect.y = row * Consts::CELL_HEIGHT;

            if (_cells[row][col] == CellState::ALIVE)
            {
                auto &blue_ref = _cell_time_alive_tracker_map.at({row, col});
                increment_in_range(blue_ref, 1, MIN_BLUE_STRENGTH);

                _renderer.set_draw_color({0, 0, blue_ref}, 0);
                _renderer.fill_rect(rect);
            }
        }
    }
}

void Game::increment_in_range(uint8_t &byte, uint8_t amount, uint8_t min_allowed_value)
{
    byte += amount;
    if (byte <= min_allowed_value)
    {
        byte = min_allowed_value;
    }
}

size_t Game::cell_rows() const
{
    return _screen_dimensions.screen_height / _cell_height;
}

size_t Game::cell_cols() const
{
    return _screen_dimensions.screen_width / _cell_width;
}
