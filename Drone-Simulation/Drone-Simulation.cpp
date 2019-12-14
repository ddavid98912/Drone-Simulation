#include <iostream>
#include "Drone3D.h"


int main()
{

	Drone3D d3d;
	std::ofstream logfile;
	d3d.initWindow(800, 900, "Drone Simulation");
	Movement* coords = new Movement(0, 0, 0, 0, 0, 0, 0, 0, 0, d3d.ti);
	
	while (!d3d.shouldClose()) {
		d3d.updateView();
	}
	d3d.closeContext();
	getchar();
}
