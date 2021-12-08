#pragma once
#include "header.h"


namespace Rendering {

float camera_x = 0.f;
float camera_y = 0.f;


// Getter functions
float get_screen_width() {
    return glutGet(GLUT_WINDOW_WIDTH);
}

float get_screen_height() {
    return glutGet(GLUT_WINDOW_HEIGHT);
}

// Draw functions
void draw_rectangle(
    float x, float y,  // position
    float size_x, float size_y,  // lengths of sides
    float z,  // depth of the square
    float red, float green, float blue,  // colour
    float alpha  // opacity
) {
    glBegin(GL_POLYGON);
    {
        glColor4f(red, green, blue, alpha);
        glVertex3f(x, y, z);
        glVertex3f(x+size_x, y, z);
        glVertex3f(x+size_x, y+size_y, z);
        glVertex3f(x, y+size_y, z);
    }
    glEnd();
}
void draw_empty_rectangle(
    float x, float y,  // position
    float size_x, float size_y,  // lengths of sides
    float border_size,  // width of the wall (to the outside)
    float z,  // depth of the square
    float red, float green, float blue,  // colour
    float alpha  // opacity
) {
    glBegin(GL_QUADS);
    {
        glColor4f(red, green, blue, alpha);
        // Bottom
        glVertex3f(x-border_size, y-border_size, z);
        glVertex3f(x+size_x+border_size, y-border_size, z);
        glVertex3f(x+size_x, y, z);
        glVertex3f(x, y, z);
        // Left
        glVertex3f(x-border_size, y-border_size, z);
        glVertex3f(x-border_size, y+size_y+border_size, z);
        glVertex3f(x, y+size_y, z);
        glVertex3f(x, y, z);
        // Top
        glVertex3f(x-border_size, y+size_y+border_size, z);
        glVertex3f(x+size_x+border_size, y+size_y+border_size, z);
        glVertex3f(x+size_x, y+size_y, z);
        glVertex3f(x, y+size_y, z);
        // Right
        glVertex3f(x+size_x+border_size, y-border_size, z);
        glVertex3f(x+size_x+border_size, y+size_y+border_size, z);
        glVertex3f(x+size_x, y+size_y, z);
        glVertex3f(x+size_x, y, z);
    }
    glEnd();
}

// Display functions
int is_fullscreen = 0;

void display_start() {
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
        80.f,  // field of view
        get_screen_width() / get_screen_height(),  // aspect ratio
        0.1f,  // min drawing distance
        10.f  // max drawing distance
    );

    // Set the camera
	gluLookAt(
        camera_x, camera_y, 1.4f,
		camera_x, camera_y, 0.f,
		0.f, 1.f, 0.f
    );
}

void display_end() {
    glutSwapBuffers();
}

void toggle_fullscreen() {
    if (is_fullscreen) {
        glutReshapeWindow(800, 600);
        glutPositionWindow(100, 100);
    } else {
        glutFullScreen();
    }
    is_fullscreen = !is_fullscreen;
}

// Control functions
int window_id;

void exit() {
    glutDestroyWindow(window_id);
}

// Helper functions
void _do_nothing() {}

void _reshape_window(int width, int height) {
    glViewport(0, 0, width, height);
}

// Main functions
void init(
    int argc, char *argv[]
) {
    // Main init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    // Create window
    window_id = glutCreateWindow("Project-Cells");
    glutReshapeWindow(800, 600);
    glutPositionWindow(100, 100);
    glutDisplayFunc(_do_nothing);
    glutReshapeFunc(_reshape_window);
    toggle_fullscreen();

    // Enable transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Enable MSAA (multisampling antialiasing)
    glEnable(GL_MULTISAMPLE);
}

void start(
    void (*frame_function)(void),
    void (*mouse_movement_function)(int, int),
    void (*mouse_key_function)(int, int, int, int),
    void (*keyboard_function)(unsigned char, int, int),
    void (*special_keyboard_function)(int, int, int)
) {
    // Attach functions
    glutIdleFunc(frame_function);
    glutMotionFunc(mouse_movement_function);
    glutMouseFunc(mouse_key_function);
    glutKeyboardFunc(keyboard_function);
    glutSpecialFunc(special_keyboard_function);

    // Start the main loop
    glutMainLoop();
}

}
