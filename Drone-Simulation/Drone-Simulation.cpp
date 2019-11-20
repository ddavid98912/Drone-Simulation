#include <iostream>
#include "globals.h"
#include "Drone3D.h"
#include "Movement.h"

int main()
{
	Drone3D d3d;
	Movement* coords = new Movement(0, 0, 0, 0, 0, 0, 0, 0, 0);
	d3d.initWindow(800, 900, "Drone Simulation");
	while (!d3d.shouldClose()) {
		d3d.updateView();
	}
	d3d.closeContext();
	getchar();
}
