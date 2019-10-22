#include "Drone3D.h"

//Functie de callback pentru input de la tastatura
void Drone3D::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//Functie de callback pentru handling ul de erori
void Drone3D::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//Creeaza o fereastra de dimensiuni date unde o sa se intample vizualizarea
void Drone3D::initWindow(int height, int width, const char* title)
{
	if (!glfwInit())
		fprintf(stderr, "Could not initialize GLFW context");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;
	GLFW_WINDOW = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, NULL, NULL);
	glfwSwapInterval(1);
	glfwSetKeyCallback(GLFW_WINDOW, key_callback);
	glfwSetErrorCallback(error_callback);
	if (!GLFW_WINDOW)
	{
		fprintf(stderr, "Error opening the GLFW window");
	}
}

//Verifica daca a fost setat flag-ul de inchidere a ferestrei
bool Drone3D::shouldClose()
{
	return glfwWindowShouldClose(GLFW_WINDOW);
}

//Anunta inchiderea ferestrei, in general nu e nevoie sa fie apelat, fereastra se inchide cu ESC
void Drone3D::closeWindow()
{
	glfwSetWindowShouldClose(GLFW_WINDOW, GLFW_TRUE);
}

//Clean-up la sfarsitul codului pt eliberarea de resurse
void Drone3D::closeContext()
{
	glfwDestroyWindow(GLFW_WINDOW);
	glfwTerminate();
}

//Aici se intampla modelarea si transformarile in OpenGL
void Drone3D::updateView()
{
	glfwSwapBuffers(GLFW_WINDOW);
	glfwPollEvents();
}

