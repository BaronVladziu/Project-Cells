#pragma once
#include "header.h"


namespace Game {

    World * _world;

    void init() {
        _world = new World(-1.f, -1.f, 2.f, 2.f, 80, 80, 0.01f);
    }

    void frame() {
        _world->update();
        _world->draw();
    }

    void clean() {
        delete _world;
    }

}
