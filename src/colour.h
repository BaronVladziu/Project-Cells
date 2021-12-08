#pragma once
#include "header.h"


struct Colour {
    float red, green, blue, alpha;
};


class ColourMap {
public:
    virtual const Colour get_colour(float value) const = 0;
};


class GrayColourMap: public ColourMap {
public:
    const Colour get_colour(float value) const {
        return Colour{value, value, value, 1.f};
    }
};


class RainbowColourMap: public ColourMap {
public:
    const Colour get_colour(float value) const {
        if (value*6.f < 1.f) {
            return Colour{0.f, 0.f, value*6.f, 1.f};
        } else if (value*6.f < 2.f) {
            return Colour{0.f, value*6.f - 1.f, 1.f, 1.f};
        } else if (value*6.f < 3.f) {
            return Colour{0.f, 1.f, 1.f - (value*6.f - 2.f), 1.f};
        } else if (value*6.f < 4.f) {
            return Colour{value*6.f - 3.f, 1.f, 0.f, 1.f};
        } else if (value*6.f < 5.f) {
            return Colour{1.f, 1.f - (value*6.f - 4.f), 0.f, 1.f};
        } else {
            return Colour{1.f, value*6.f - 5.f, value*6.f - 5.f, 1.f};
        }
    }
};


class HeatColourMap: public ColourMap {
public:
    const Colour get_colour(float value) const {
        if (value*3.f < 1.f) {
            return Colour{value*3.f, 0.f, 0.f, 1.f};
        } else if (value*3.f < 2.f) {
            return Colour{1.f, value*3.f - 1.f, 0.f, 1.f};
        } else {
            return Colour{1.f, 1.f, value*3.f - 2.f, 1.f};
        }
    }
};


class PinkColourMap: public ColourMap {
public:
    const Colour get_colour(float value) const {
        if (value*3.f < 1.f) {
            return Colour{
                (131.f/255.f)*(value*3.f),
                (212.f/255.f)*(value*3.f),
                (255.f/255.f)*(value*3.f),
                1.f
            };
        } else if (value*3.f < 2.f) {
            return Colour{
                (131.f/255.f) + (255.f/255.f - 131.f/255.f)*(value*3.f - 1.f),
                (212.f/255.f) + (197.f/255.f - 212.f/255.f)*(value*3.f - 1.f),
                (255.f/255.f) + (255.f/255.f - 255.f/255.f)*(value*3.f - 1.f),
                1.f
            };
        } else {
            return Colour{
                (255.f/255.f) + (255.f/255.f - 255.f/255.f)*(value*3.f - 2.f),
                (197.f/255.f) + (255.f/255.f - 197.f/255.f)*(value*3.f - 2.f),
                (255.f/255.f) + (255.f/255.f - 255.f/255.f)*(value*3.f - 2.f),
                1.f
            };
        }
    }
};
