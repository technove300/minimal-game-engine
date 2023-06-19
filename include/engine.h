#ifndef engine_h
#define engine_h

#define GLEW_STATIC

#define DO_INTEL_WORKAROUND false

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GL/glew.h"
#include <GL/glu.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "graphics.h"

#define TITLE "minimal game engine"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

extern int errorCode;
extern int exitLoop;

extern float degrees;
extern double deltaTime;
extern double time;
extern ParticleSystem *p1;

extern mat4 viewMatrix;
extern mat4 projectionMatrix;

vec3 c_pos = {{0, 0, 3}};
vec3 c_front = {{0, 0, -1}};
vec3 c_up = {{0, 1, 0}};

float fov = 60.0f;
int s_width = SCREEN_WIDTH;
int s_height = SCREEN_HEIGHT;



int init();
int initGL();
void quit();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void error_callback(int error, const char* description);
void key_input_poll(void);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

extern GLFWwindow *window;




#endif