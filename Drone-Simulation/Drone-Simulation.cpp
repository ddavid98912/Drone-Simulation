#include <iostream>
#include "Drone3D.h"

int main()
{
	Drone3D d3d;
	d3d.initWindow(800, 900, "Drone Simulation");
	while (!d3d.shouldClose()) {
		d3d.updateView();
	}
	d3d.closeContext();
	getchar();
}
