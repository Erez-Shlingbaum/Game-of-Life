#include <cstdint>
#include <utility>
#include <SDL.h>
#include <array>
#include <iostream>
#include "game.hpp"
#include "cell.hpp"
#include "constants.hpp"
#include "sdl_wrappings.hpp"

Game::Game(std::string title, size_t screen_width, size_t screen_height, size_t cell_width, size_t cell_height) :
        _title(std::move(title)),
        _screen_width(screen_width),
        _screen_height(screen_height),
        _cell_width(cell_width),
        _cell_height(cell_height),
        _cell_rows(cell_rows()),
        _cell_cols(cell_cols()),
        _neighbour_counts(_cell_rows, std::vector<CountCell>(_cell_cols, {CellState::DEAD, 0})),
        _cells(_cell_cols, std::vector<CellState>(_cell_cols, CellState::DEAD)),
        _window(_title.c_str(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                static_cast<int>(_screen_width), static_cast<int>(_screen_height),
                SDL_WINDOW_FULLSCREEN),
        _renderer(_window, -1, SDL_RENDERER_ACCELERATED)
{
    SDL_SetWindowBordered(_window, SDL_FALSE);
    init_cells();
}

void Game::run()
{
    SDL_Event event = {0};

    while (handle_events(event))
    {
        update();
        draw();

        SDL_Delay(Consts::FPS);
    }
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

bool Game::is_valid_position(size_t row, size_t col) const
{
    return (0 <= row && row < _cell_rows) && (0 <= col && col < _cell_cols);
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
                if (is_valid_position(row + i, col + j))
                {
                    count += _cells[row + i][col + j] == CellState::ALIVE;
                }
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
    SDL_Rect rect{0, 0, CELL_WIDTH, CELL_HEIGHT};

    _renderer.set_draw_color(Color::BLUE, 0);
    for (int row = 0; row < _cell_rows; ++row)
    {
        for (int col = 0; col < _cell_cols; ++col)
        {
            rect.x = col * CELL_WIDTH;
            rect.y = row * CELL_HEIGHT;

            if (_cells[row][col] == CellState::ALIVE)
            {
                _renderer.fill_rect(rect);
            }
        }
    }
}

size_t Game::cell_rows() const
{
    return _screen_height / _cell_height;
}

size_t Game::cell_cols() const
{
    return _screen_width / _cell_width;
}