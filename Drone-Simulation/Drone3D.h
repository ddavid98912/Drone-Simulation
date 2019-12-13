#pragma once
#pragma comment(lib, "headers/glfw3.lib")
#include "headers/glfw3.h"
#include <stdio.h>
#include "Movement.h"
#include "PID.h"
#include "PIDr.h"	


union Color
{
	GLfloat rgb[3];
};


class Drone3D
{
	GLFWwindow* GLFW_WINDOW = NULL;
	float r = 0;
	int WINDOW_HEIGHT, WINDOW_WIDTH;
	static Movement* coords;
	static PID* control;
	static float ref[3];

	
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void error_callback(int error, const char* description);
	void drawCube(float* pos, float* size, float* rot, Color* color);
	static void reshape(GLFWwindow * window, int width, int height);
	void drawBody();
	void drawRotor(int index);

	void drawTerrain();

public:
	TerrainInfo ti;
	//Initializeaza o fereastra asociata unui context OpenGL
	Drone3D();
	void initWindow(int height, int width, const char * title);
	bool shouldClose();
	void closeWindow();
	void closeContext();
	void drawDrone();
	void updateView();
	void updateVel(double, double, double);
};


