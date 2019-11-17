#include <iostream>
#include "globals.h"
#include "Drone3D.h"
#include "Movement.h"

int main()
{
	Drone3D d3d;
	Movement* coords = new Movement(0, 0, 0, 0, 0, 0, 0.000001, 0, -0.000001);
	d3d.initWindow(800, 900, "Drone Simulation");
	std::cout << mass << std::endl;
	while (!d3d.shouldClose()) {
		d3d.updateView(coords);
	}
	d3d.closeContext();
	getchar();
}
