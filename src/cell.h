#pragma once
#include "header.h"


class Cell {
    float _value;

public:
    Cell() : _value(0.f) {}
    Cell(float value) {
        if (value > 1.f) {
            _value = 1.f;
        } else if (value < 0.f) {
            _value = 0.f;
        } else {
            _value = value;
        }
    }
    const float get_value() const {
        return _value;
    }
    Cell& operator=(const Cell& other) {
        _value = other._value;
        return *this;
    }
};
