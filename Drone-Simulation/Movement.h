#pragma once
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
public :
	friend class Drone3D;
	//primii 3 parametri sunt coordonatele initiale, urmatorii 3 vitezele pe cele 3 axe si urmatorii 3 acceleratiile pe cele 3 axe
	Movement(double, double, double, double, double, double, double, double, double);
	void update();
};

