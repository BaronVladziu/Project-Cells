#pragma once
#include "header.h"


class Kernel {
public:
    virtual const float get_mapping_for(int x, int y) const = 0;
    virtual const float get_map_start_x() const = 0;
    virtual const float get_map_end_x() const = 0;
    virtual const float get_map_start_y() const = 0;
    virtual const float get_map_end_y() const = 0;
    virtual float growth_function(float neighborhood_value) const = 0;
};


class ConwayKernel: public Kernel {
public:
    const float get_mapping_for(int x, int y) const {
        if (abs(x) == 1 || abs(y) == 1) {
            return 1;
        } else {
            return 0;
        }
    }

    const float get_map_start_x() const {
        return -1;
    }
    const float get_map_start_y() const {
        return -1;
    }
    const float get_map_end_x() const {
        return 1;
    }
    const float get_map_end_y() const {
        return 1;
    }
    
    float growth_function(float neighborhood_value) const {
        if (neighborhood_value < 1.5f) {
            return -1;
        } else if (neighborhood_value < 2.5f) {
            return 0;
        } else if (neighborhood_value < 3.5f) {
            return 1;
        } else {
            return -1;
        }
    }
};


class LeniaKernel: public Kernel {
    const float _triangle(float x, float start, float center, float end) const {
        if (x < start) {
            return 0.f;
        } else if (x < center) {
            return (x-start)/(center-start);
        } else if (x < end) {
            return 1.f - (x-center)/(end-center);
        } else {
            return 0.f;
        }
    }
    const float _mapping_function(int x, int y) const {
        // Get distance
        float value = std::sqrt(x*x + y*y);
        // Apply gaussian function
        value = _triangle(value, 2.f, 5.f, 8.f);
        // Return
        return value;
    }
    std::vector<std::vector<float>> _mapping;
    float _mapping_volume;

public:
    LeniaKernel() {
        // Calculate mapping
        _mapping = std::vector<std::vector<float>>();
        _mapping_volume = 0.f;
        for (
            int x = get_map_start_x();
            x <= get_map_end_x();
            x++
        ) {
            _mapping.push_back(std::vector<float>());
            for (
                int y = get_map_start_y();
                y <= get_map_end_y();
                y++
            ) {
                _mapping[x - get_map_start_x()].push_back(_mapping_function(x, y));
                _mapping_volume += _mapping[x - get_map_start_x()][y - get_map_start_y()];
            }
        }
    }

    const float get_mapping_for(int x, int y) const {
        return _mapping[x - get_map_start_x()][y - get_map_start_y()];
    }

    const float get_map_start_x() const {
        return -8;
    }
    const float get_map_start_y() const {
        return -8;
    }
    const float get_map_end_x() const {
        return 8;
    }
    const float get_map_end_y() const {
        return 8;
    }

    float growth_function(float neighborhood_value) const {
        float side = 2.8f;
        float center = 11.09f;
        return 0.2f*_triangle(
            neighborhood_value,
            center - side,
            center,
            center + side
        ) - 0.1f;
    }
};
