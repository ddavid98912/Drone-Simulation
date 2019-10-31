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

void Drone3D::drawCube(float * pos, float * size, float * rot)
{
	glPushMatrix();
	glScalef(size[0], size[1], size[2]);
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[0], 1.0, 0.0, 0.0);
	glRotatef(rot[1], 0.0, 1.0, 0.0);
	glRotatef(rot[2], 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);               

	glColor3f(0.0f, 1.0f, 0.0f);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();  // End of drawing color-cube
	glPopMatrix();
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
	glfwSetFramebufferSizeCallback(GLFW_WINDOW, reshape);
	glfwMakeContextCurrent(GLFW_WINDOW);
	if (!GLFW_WINDOW)
	{
		fprintf(stderr, "Error opening the GLFW window");
	}

	GLint h, w;
	glfwGetFramebufferSize(GLFW_WINDOW, &w, &h);
	reshape(GLFW_WINDOW, w, h);

	//OpenGL init and window hints
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

//Verifica daca a fost setat flag-ul de inchidere a ferestrei
bool Drone3D::shouldClose()
{
	return glfwWindowShouldClose(GLFW_WINDOW);
}

void Drone3D::reshape(GLFWwindow* window, int width, int height)
{
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 30.0f;
	xmax = znear * 0.5f;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xmax, xmax, -xmax * h, xmax * h, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	//Rotatie pt camera
	glLoadIdentity();                 // Reset the model-view matrix
	glRotatef(20, 1.0f, 0.0f, 0.0f); //Rotatie pe X
	glRotatef(0, 0.0f, 1.0f, 0.0f); //Rotatie pe Y
	glRotatef(0, 0.0f, 0.0f, 1.0f); //Rotatie pe Z
	glTranslatef(0.0f, -13.0f, -20.0f);  // Move right and into the screen

	r = r + 0.1;
	float size[] = { 2.0f, 2.0f, 2.0f };
	float pos[] = { 0.0f, 0.0f, 0.0f };
	float rotation[] = { 0.0f, r, 0.0f };
	drawCube(pos, size, rotation);

	glfwSwapBuffers(GLFW_WINDOW);
	glfwPollEvents();
}

