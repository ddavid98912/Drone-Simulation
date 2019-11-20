#pragma once
#include "globals.h"
#include "Force.h"
class Movement
{
public :
	//coordonate
	double x, y, z;
	//viteze
	double vx, vy, vz;
	//acceleratii
	double ax, ay, az;
	//timp
	double time = 0;
	double time_step = 0;
	//forte
	//forte[0] fata-stanga, forta[1] fata-dreapta, forta[2] spate-stanga, forta[3] spate-stanga
	Force forte[4];
	//rezultantele fortelor pe axe
	Force res;
	Force frecare;
public :
	friend class Drone3D;
	//primii 3 parametri sunt coordonatele initiale, urmatorii 3 vitezele pe cele 3 axe si urmatorii 3 acceleratiile pe cele 3 axe
	Movement(double, double, double, double, double, double, double, double, double);
	void update();
	void updateForces();
	void modVel(double, double, double);
};

