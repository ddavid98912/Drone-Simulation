#include "Drone3D.h"
#include "globals.h"

Movement* Drone3D::coords;

Drone3D::Drone3D() {
	coords = new Movement(0, 0, 0, 0, 0, 0, 0, 0, 0);
}

//Functie de callback pentru input de la tastatura
void Drone3D::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		coords->vz = -0.6;
	}
	else if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
		coords->vz = 0;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		coords->vz = 0.6;
	}
	else if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
		coords->vz = 0;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		coords->vx = -0.6;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		coords->vx = 0;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		coords->vx = 0.6;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		coords->vx = 0;
	}
}

//Functie de callback pentru handling ul de erori
void Drone3D::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Drone3D::drawCube(float* pos, float* size, float* rot, Color * color)
{
	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(size[0], size[1], size[2]);
	
	glRotatef(rot[0], 1.0, 0.0, 0.0);
	glRotatef(rot[1], 0.0, 1.0, 0.0);
	glRotatef(rot[2], 0.0, 0.0, 1.0);
	glBegin(GL_QUADS);               

	glColor3fv(color[0].rgb);     // Green
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Bottom face (y = -1.0f)
	glColor3fv(color[1].rgb);   // Orange
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Front face  (z = 1.0f)
	glColor3fv(color[2].rgb);     // Red
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Back face (z = -1.0f)
	glColor3fv(color[3].rgb);     // Yellow
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Left face (x = -1.0f)
	glColor3fv(color[4].rgb);    // Blue
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face (x = 1.0f)
	glColor3fv(color[5].rgb);    // Magenta
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

//Nu se atinge nimeni de asta
void Drone3D::reshape(GLFWwindow* window, int width, int height)
{
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 150.0f;
	xmax = znear * 0.5f;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xmax, xmax, -xmax * h, xmax * h, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
}

void Drone3D::drawBody()
{
	float size[] = { width, height, length };
	float pos[] = { 0, 0, 0 };
	float rotation[] = { 0, 0, 0 };
	//top, bottom, front, back, left right:
	Color cyan = { {0.0, 1.0, 1.0} };
	Color pale_green = { {0.8, 1.0, 0.6} };
	Color red = { {1.0, 0.3, 0.3} };
	Color c[6] = { cyan, cyan, red, red, pale_green, pale_green };
	drawCube(pos, size, rotation, c);
}

void Drone3D::drawRotor(int index)
{
	float rotor_size[3] = { 1.0f, 0.3f, 1.0f };
	float rotor_pos[4][3] = { {  width, height + rotor_size[1],  length},
							  { -width, height + rotor_size[1],  length},
							  { -width, height + rotor_size[1], -length},
							  {  width, height + rotor_size[1], -length} };
	float rotor_rotation[] = { 0.0f, r, 0.0f };
	if (index % 2 == 0) {
		rotor_rotation[1] *= -1;
	}

	//top, bottom, front, back, left right:
	Color top = { {0.5, 0.0, 0.0} };
	Color side1 = { {1.0, 0.0, 1.0} };
	Color side2 = { {0.0, 1.0, 0.0} };
	Color c[6] = { top, top, side1, side1, side2, side2 };

	drawCube(rotor_pos[index], rotor_size, rotor_rotation, c);

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

void Drone3D::drawDrone() {
	//Totul este desenat cu drona in (0, 0, 0), apoi translatat si rotit ca ansamblu ca sa mearga mai usor
	r++; //rotatia elicilor

	glPushMatrix();
	drawBody();
	for (int i = 0; i < 4; i++) {
		drawRotor(i);
	}
	glPopMatrix();
}

void Drone3D::updateVel(double dVx, double dVy, double dVz) {
	coords->modVel(dVx, dVy, dVz);
}

//Aici se intampla modelarea si transformarile in OpenGL
void Drone3D::updateView()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	coords->update();

	//Rotatie pt camera
	glLoadIdentity();                 // Reset the model-view matrix
	glRotatef(20, 1.0f, 0.0f, 0.0f); //Rotatie pe X
	glRotatef(0, 0.0f, 1.0f, 0.0f); //Rotatie pe Y
	glRotatef(0, 0.0f, 0.0f, 1.0f); //Rotatie pe Z
	glTranslatef(0.0f, -13.0f, -25.0f);  // Move right and into the screen
	//Atat a fost pentru setarea perspectivei
	glPushMatrix();
	glTranslatef(coords->x, coords->y, coords->z);
	drawDrone();
	glPopMatrix();
	glfwSwapBuffers(GLFW_WINDOW);
	glfwPollEvents();
}

