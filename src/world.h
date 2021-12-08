#pragma once
#include "header.h"


class World {
    float _pos_x, _pos_y, _size_x, _size_y, _border_width;
    const int _number_of_cells_x, _number_of_cells_y;
    std::vector<std::vector<Cell>> _cells;
    Cell _void_cell;

    std::unique_ptr<ColourMap> _colour_map = std::unique_ptr<ColourMap>(
        new PinkColourMap()
    );
    std::unique_ptr<Kernel> _kernel = std::unique_ptr<Kernel>(
        new LeniaKernel()
    );

public:
    World(
        float pos_x, float pos_y,
        float size_x, float size_y,
        int number_of_cells_x, int number_of_cells_y,
        float border_width
    );
    const Cell & get_cell(int x, int y) const;
    void update();
    void draw();
};
