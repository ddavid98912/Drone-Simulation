#pragma once
#include <cmath>
#include "globals.h"

class Force
{
	//componentele pe x, y, z
	double x, y, z;
	//amplitudinea fortei
	double magnitude = 0;
	//unghiurile fata de cele 3 axe
	double pitch = 0, yaw = 0, roll = 0;
	//momentele
	double mom[3] = { 0, 0, 0 };
public:
	Force();
	Force(double, double, double);
	void calcComp();
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	void set(double, double, double);
	void setAngles(double, double, double);
	void setMag(double mag);
	void addForce(Force);
	void addForce(double, double, double);
	double* calcMom(double* bF);
};

