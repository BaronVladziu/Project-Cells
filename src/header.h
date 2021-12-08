#pragma once

// OpenGL and GLUT
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <GL/freeglut.h> 

// C++ libs
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>
#include <vector>

// Basic function headers
#include "logging.h"
#include "rendering.h"

// Game classes
#include "kernels.h"
#include "cell.h"
#include "colour.h"
#include "world.h"
#include "world.cpp"

// Other function headers
#include "controls.h"
#include "game.h"
