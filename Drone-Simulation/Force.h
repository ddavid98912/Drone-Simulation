#pragma once
#include <cmath>
class Force
{
	//componentele pe x, y, z
	double x, y, z;
	//amplitudinea fortei
	double magnitude;
	//unghiurile fata de cele 3 axe
	double unghiX, unghiY, unghiZ;
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
	void setMag(double mag);
	void addForce(Force);
	void addForce(double, double, double);
};

