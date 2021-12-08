#include "world.h"

World::World(
    float pos_x, float pos_y,
    float size_x, float size_y,
    int number_of_cells_x, int number_of_cells_y,
    float border_width
) :
    _pos_x(pos_x), _pos_y(pos_y),
    _size_x(size_x), _size_y(size_y),
    _border_width(border_width),
    _number_of_cells_x(number_of_cells_x),
    _number_of_cells_y(number_of_cells_y),
    _cells(_number_of_cells_x, std::vector<Cell>(_number_of_cells_y))
{
    for (int i = 0; i < _number_of_cells_x; i++) {
        for (int j = 0; j < _number_of_cells_y; j++) {
            // Generate random values in the centre
            float value = 0.f;
            if (i > _number_of_cells_x/3.f && i < 2.f*_number_of_cells_x/3.f) {
                if (j > _number_of_cells_y/3.f && j < 2.f*_number_of_cells_y/3.f) {
                    value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                }
            }
            // Create cell from value
            _cells[i][j] = Cell(value);
        }
    }
};

// const Cell & World::get_cell(int x, int y) const {
//     // Allow cells to teleport between walls
//     while (x < 0) {
//         x += _number_of_cells_x;
//     }
//     while (y < 0) {
//         y += _number_of_cells_y;
//     }
//     while (x >= _number_of_cells_x) {
//         x -= _number_of_cells_x;
//     }
//     while (y >= _number_of_cells_y) {
//         y -= _number_of_cells_y;
//     }
//     return _cells[x][y];
// };

const Cell & World::get_cell(int x, int y) const {
    // Only death behind the walls
    if (x < 0 || y < 0 || x >= _number_of_cells_x || y >= _number_of_cells_y) {
        return _void_cell;
    }
    return _cells[x][y];
};

void World::update() {
    std::vector<std::vector<Cell>> _new_cells(
        _number_of_cells_x, std::vector<Cell>(_number_of_cells_y)
    );
    for (int i = 0; i < _number_of_cells_x; i++) {
        for (int j = 0; j < _number_of_cells_y; j++) {
            // Get neighborhood value
            float neighborhood_value = 0.f;
            for (
                int x = _kernel->get_map_start_x();
                x <= _kernel->get_map_end_x();
                x++
            ) {
                for (
                    int y = _kernel->get_map_start_y();
                    y <= _kernel->get_map_end_y();
                    y++
                ) {
                    neighborhood_value += _kernel->get_mapping_for(x, y) * this->get_cell(
                        i + x, j + y
                    ).get_value();
                }
            }
            // Grow new cell
            _new_cells[i][j] = Cell(
                _cells[i][j].get_value() + _kernel->growth_function(neighborhood_value)
            );
        }
    }
    _cells = _new_cells;
};

void World::draw() {
    // Calculate cell size
    float cell_size_x = (_size_x-2*_border_width)/_number_of_cells_x;
    float cell_size_y = (_size_y-2*_border_width)/_number_of_cells_y;
    // Draw world border
    Rendering::display_start();
    Rendering::draw_empty_rectangle(
        _pos_x+_border_width, _pos_y+_border_width,
        _size_x-2*_border_width, _size_y-2*_border_width,
        _border_width, 0.f,
        1.f, 1.f, 1.f, 1.f
    );
    // Draw cells
    for (int i = 0; i < _number_of_cells_x; i++) {
        for (int j = 0; j < _number_of_cells_y; j++) {
            // Get cell value
            float cell_value = _cells[i][j].get_value();
            // Find colour from cell value
            Colour colour = _colour_map->get_colour(cell_value);
            // Draw cell
            Rendering::draw_rectangle(
                _pos_x+_border_width + i*cell_size_x,  // pos_x
                _pos_y+_border_width + j*cell_size_y,  // pos_y
                cell_size_x, cell_size_y,  // lengths of sides
                0.f,  // pos_z
                colour.red, colour.green, colour.blue, colour.alpha  // colour
            );
        }
    }
    Rendering::display_end();
};
