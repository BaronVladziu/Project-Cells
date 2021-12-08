#include "header.h"


int main(int argc, char *argv[]) {
    Rendering::init(
        argc, argv
    );
    Game::init();
    Rendering::start(
        Game::frame,
        Controls::mouse_movement,
        Controls::mouse_key,
        Controls::keyboard,
        Controls::special_keyboard
    );
    Game::clean();
    return 0;
}
