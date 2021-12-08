#pragma once
#include "header.h"


namespace Controls {

void mouse_movement(int x, int y) {}

void mouse_key(int button, int state, int x, int y) {}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'f':
            Rendering::toggle_fullscreen();
            break;
        case 27: // Escape key
            Rendering::exit();
            break;
    }
}

void special_keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F4:
            Rendering::toggle_fullscreen();
            break;
    }
}

}
